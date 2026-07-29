# Cascade White — Trainer AI Guide

## Move Selection (WIP)

This document covers the trainer AI move-selection scripts as they exist in **Cascade White**, a Gen V romhack built on the Black/White engine. It is a companion to `Gen5EnemyAI.md` (DaSquyd's vanilla Gen V AI documentation) but is written to stand on its own — you shouldn't need the vanilla doc open to understand what's described here, though notes are included wherever Cascade White's behavior deviates meaningfully from vanilla Black/White/Black 2/White 2, since a lot of the design intent only makes sense in that context.

Cascade White backports a large number of abilities, items, and moves from later generations (up through roughly Gen 9) into the Gen V engine, and the AI scripts have been extensively rewritten to understand them — new immunity abilities, new held items that punch through ability-based immunities, and generally smarter handling of status/stat moves. Five scripts drive move selection:

| Script | File | Role |
| --- | --- | --- |
| 0 | `PrioritizeEffectiveness` | Discourages moves that would fail, whiff, or otherwise have no effect; also lightly biases some situational status/utility moves. |
| 1 | `EvaluateAttacks` | Scores damaging moves — rewards KOs and the single strongest attack, with extra logic for priority moves, two-turn moves, and spread moves in multi-battles. |
| 2 | `Expert` | The largest script; general-purpose "smart" decision making used by boss-tier trainers. |
| 3 | `StatusDecisions` | Entirely new to Cascade White (no vanilla equivalent) — decides how eagerly to use setup, debuff, and priority moves based on the current turn's threat assessment. |
| 7 | `Doubles` | Double/Triple Battle awareness — avoiding/exploiting ally interactions, spread move targeting, etc. |

Each script returns an additive score modifier (starting from a baseline of 100 for the move, same as vanilla) that's evaluated once per legal move against each legal target; the AI selects randomly among whichever moves end up tied for the highest total score. See `Gen5EnemyAI.md` Part VI.I if you want the mechanics of how these scripts get invoked (single vs. double vs. rotation battle looping, tie-breaking, etc.) — that part of the engine is untouched by Cascade White.

---

## Script 0: PrioritizeEffectiveness {#script-0}

Vanilla name: **"No Effect."** Cascade White keeps the same fundamental job — heavily discourage (or occasionally lightly reward) a move based on whether it will actually accomplish anything — but the ability/item coverage has been substantially expanded and several vanilla bugs have been fixed along the way.

### Overall flow

1. If the target is an ally, skip straight to the end (no penalty/reward — ally-targeting logic lives in Script 7).
2. Simulate the move's damage. If it would deal zero damage, skip the type-effectiveness gate entirely and jump straight to the immunity-ability gate below.
3. **Immunity-ability gate:** if the move's type would otherwise connect, check whether the defender has an ability that grants a full immunity beyond raw type-effectiveness, and route to a **-12** penalty if so. Ignoring abilities (Mold Breaker, Turboblaze, Teravolt, or a held Ability Drill/Tera Drill — see below) skips this whole gate.
4. **Powder gate:** for the six powder moves (Sleep Powder, Poison Powder, Stun Spore, Spore, Cotton Spore, Rage Powder), check Overcoat, Safety Goggles, Sap Sipper, and Grass typing; any of them blocks the powder and applies a **-10**.
5. **Sound gate:** for sound-based moves, check the sound-immunity ability; blocks and applies **-10**.
6. **Wind gate:** for wind-based moves, check the wind-immunity ability; blocks and applies **-10**.
7. **Bomb/ball gate:** for ball-and-bomb moves, check Bulletproof; blocks and applies **-10**.
8. If type effectiveness is 0×, apply a flat **-10** and stop.
9. Otherwise, jump into a table of ~150 move-effect-specific handlers (one per distinct secondary effect a move can have — stat changes, status conditions, weather, hazards, healing, etc.), each of which checks the specific fail conditions for that effect (target already has that stat maxed/minned, target already has a status, side condition blocking it like Safeguard/Mist, relevant type or ability immunity, and so on) and applies a penalty — usually **-10**, sometimes **-8**, **-12**, **-6**, or **-5** for softer cases — if the effect would do nothing.

Damaging moves themselves (the `dmg` effect and its many damage+status/stat variants) fall straight through to the end with no adjustment here — pure damage scoring is Script 1's job, not Script 0's.

### The "ignore ability" group

Anywhere the script needs to check whether the *defender's* ability would block an effect, it first checks whether the *attacker* can bypass abilities altogether. In Cascade White this bypass triggers on any of:

- Ability **Mold Breaker**, **Turboblaze**, or **Teravolt**
- Held item **Ability Drill** or **Tera Drill**

The two items are Cascade White additions — consumable-less held items that grant Mold-Breaker-style ability-ignoring without needing the ability itself. This bypass check is repeated consistently in front of nearly every ability-immunity check in the script (there are dozens of them), so a Pokémon holding either item behaves, for AI-decision purposes, exactly like it has Mold Breaker.

> **Vanilla note:** Stock Black/White only checks Mold Breaker for this. Turboblaze and Teravolt (Gen V's other two ability-ignoring abilities) were never added to the vanilla AI's bypass checks at all. Cascade White fixes this.

### Type-immunity abilities (step 3)

| Immunity | Abilities checked |
| --- | --- |
| Electric | Volt Absorb, Motor Drive, Lightning Rod, **Thunder Armor** |
| Water | Water Absorb, **Storm Drain**, **Dry Skin** |
| Fire | Flash Fire, **Well-Baked Body** |
| Ground | Levitate |
| Grass | Sap Sipper |
| All damage (if not 2×/4×) | Wonder Guard |

Bolded entries are either genuinely new to this check or fixes of vanilla bugs:

- **Storm Drain is a bug fix.** Vanilla Black/White has a well-known bug (documented in `Gen5EnemyAI.md` under "Storm Drain Bug") where the immunity check for Storm Drain was accidentally duplicated as a second, redundant Levitate check, so the vanilla AI happily spams Water-type moves into Storm Drain users. Cascade White's script checks `ability.storm_drain` directly and correctly routes it to the water-immunity branch.
- **Dry Skin** is likewise correctly wired to the water-immunity branch (it isn't a true immunity in the actual battle engine — Dry Skin takes half damage from Water rather than none — but the AI script treats it as a full "don't bother" case, presumably because attacking into it is nearly always a bad idea anyway).
- **Thunder Armor** and **Well-Baked Body** are abilities not present in vanilla Gen V (Well-Baked Body is a real Gen IX ability; Thunder Armor is a Cascade White original filling the "fourth Electric immunity" slot). Both are wired in exactly like their vanilla siblings.

### New immunity categories not present in vanilla at all

Three entire immunity checks were added wholesale — none of these existed in the Black/White AI, since the mechanics themselves (Gen VI's powder/Overcoat interaction, Gen VI's Bulletproof, Gen VIII's Wind Rider) postdate Gen V:

- **Powder immunity** — Grass-types, Overcoat, Sap Sipper, and a held Safety Goggles all cause the AI to write off Sleep Powder / Poison Powder / Stun Spore / Spore / Cotton Spore / Rage Powder as a **-10**.
- **Sound immunity** — a dedicated ability (checked in the script as `ability.amplifier`) causes the AI to write off sound-based moves. Notably the move list checked includes **Hyper Voice**, along with the expected Growl/Roar/Sing/Screech/Uproar/etc. and several later-gen sound moves (Disarming Voice, Clanging Scales, Alluring Voice, Boomburst, Psychic Noise).
  > **Vanilla note:** this is also a bug fix. Vanilla's equivalent Soundproof check (documented as the "Soundproof Bug") omits Hyper Voice from its move list, so the stock AI will freely use Hyper Voice into a Soundproof Pokémon. Cascade White's list includes it.
- **Wind immunity** — Wind Rider causes the AI to write off wind-based moves (Icy Wind, Air Slash, Hurricane, Heat Wave, Gust, Twister, Whirlwind, etc.).
- **Bomb/ball immunity** — Bulletproof causes the AI to write off ball-and-bomb moves (Focus Blast, Shadow Ball, Sludge Bomb, Energy Ball, Aura Sphere, Rock Blast, etc.).

### Stat-change handlers

Raising/lowering each stat has its own handler, largely unchanged in shape from vanilla (don't raise a stat that's already at +6; don't lower a stat that's already at -6; skip Speed changes entirely under Trick Room since they'd be counterproductive), but the "the target can just ignore this" checks have been broadened:

- The group of abilities that make a stat-lowering move pointless (Clear Body-style full stat-drop immunity) now includes **Unaware** alongside the usual suspects, and the vanilla ability is renamed **Strong Body** in this hack's ability set (functionally identical to Clear Body).
- **Defiant** and the new **Unaware** both trigger a harsher **-12** (rather than the standard -10) when the AI tries to lower Attack, since Defiant actively backfires by boosting the target instead.
- **Unnerve** on the attacker disables the "target is probably holding a stat-protecting berry (White Herb/Mental Herb)" chance-based penalty, since Unnerve prevents berries from being eaten at all — the AI correctly stops worrying about the berry once it knows Unnerve is active.

### Status-move handlers

Each major status condition (Sleep, Poison/Toxic, Burn, Paralysis, Confusion) follows the same pattern: check if the target already has a status/is protected by Safeguard or Mist, check the relevant type immunity, then check abilities. The ability lists have been extended well past vanilla's Gen V roster:

- **Paralysis** now also declines to paralyze targets with **Marvel Scale**, **Guts**, or **Quick Feet** — all abilities that actively *benefit* from being paralyzed (or from status in general), so the AI avoids handing the opponent a buff.
- **Poison/Toxic** similarly declines against **Toxic Boost** (benefits from poison).
- **Burn**-inflicting moves (Will-O-Wisp, Psycho Shift, Scald-style fling burns, etc.) decline against **Flare Boost** and **Guts** (both benefit from burn) in addition to the expected Fire-type immunity, Water Veil, Heatproof, and Magic Guard.
- Each of these also carries an **Unnerve** check that suppresses the "likely holding a cure berry" soft penalty, matching the stat-drop logic above.


### Gastro Acid: from pure-fail-check to opportunistic play
This is the single most significant behavioral upgrade in Script 0. Vanilla Gastro Acid AI only checks whether the move would fail outright (target already has no ability / already Gastro-Acid'd / has one of a few uneditable abilities like Multitype). Cascade White adds a second layer: after confirming the move would *work*, it checks whether the target's ability is one that's actively helping them —

- **Guts, Sheer Force, Adaptability, Huge Power, Pure Power** — raw offensive/defensive boosts, or
- Any of the type-immunity abilities (**Storm Drain, Water Absorb, Dry Skin, Flash Fire, Well-Baked Body, Lightning Rod, Volt Absorb, Thunder Armor, Motor Drive, Levitate, Sap Sipper**) *if* the attacker's own type would otherwise be blocked by it

— and if so, has a 100/256 (~39%) chance to add **+2** to Gastro Acid's score, actively encouraging the AI to strip a beneficial or inconvenient ability rather than only using Gastro Acid as a last resort against a move that would otherwise fail.

### Other notable behaviors

- **Fake Out / first-impression-style priority moves** are penalized **-15** (rather than being disabled outright) if it isn't the user's first turn on the field — a much steeper penalty than the standard -10, effectively ensuring these almost never get picked outside their intended window
- **Knock Off** has a chance (75/256, ~29%) to receive a **+2** bonus if the target is holding any item at all
- **Tailwind** has a chance (56/256, ~22%) to receive a **+2** bonus in multi-battles specifically
- **Stockpile / Spit Up / Swallow** check the user's held item against a full berry list, and specifically against a "stat berry" sub-list (Liechi, Ganlon, Salac, Petaya, Apicot, Roseli, Starf, Kee, Maranga) for a chance at a small bonus.
- **Fling** now branches on three item categories (poison-inducing, burn-inducing, paralysis-inducing) and runs the same "would this status backfire or fail" logic as the dedicated status-move handlers above, rather than vanilla's simpler pass/fail check.

---

## Script 1: EvaluateAttacks {#script-1}
This is the "does this move actually hit hard, and should I care" script — it's the only place damaging moves get a positive score contribution for being a strong attack or a KO.

### Baseline mechanic: the "strongest move" simulation
Before this script runs, the engine simulates the user's attack against the target once per move being scored, using `CalcMoveDamage`. This simulation has some engine-level quirks (unchanged from vanilla, since they're part of the underlying damage-calc routine rather than script logic):

- The result is compared against the *strongest* move the attacker has available this turn, and Script 1 receives a simple "is this the strongest move, or not" flag rather than a damage number.
- The simulated roll always uses the lowest of the 16 possible damage rolls (85%) with no critical hit, so a move only counts as a guaranteed KO if even its worst-case roll would faint the target.
- Move-event listeners aren't bound during this simulation, so variable base power moves are evaluated at their listed base value (e.g. Pin Missile as 14 BP even with Skill Link, Frost Breath as 40 despite always critting) and type-changing effects (Judgment, Weather Ball) are simulated as their default type.
- Everything else about the damage formula — abilities, items, burn halving, Huge Power/Pure Power, gems, Normalize, etc. — is respected normally.

### If the move is not the target's strongest option

```
not the strongest move → −1
is the strongest move, and is Explosion / Focus Punch / Sucker Punch → 20% (51/256) chance of an extra −2
then: if the move is at least super effective (2× or 4×) → 31% (80/256) chance of +2
```

Every non-strongest damaging move just takes a flat **-1**, same as vanilla. For the strongest move, the small risk-based penalty for all-or-nothing moves (Explosion/Focus Punch/Sucker Punch — moves that can fail outright or leave the user unable to act) is unchanged from vanilla. The one real change here: **vanilla only rolled the "is this super effective, give it a nudge" bonus off 4× effectiveness; Cascade White also grants the same chance at merely 2× effectiveness.** This makes the AI mildly more willing to lean on any super-effective STAB/coverage move that happens to be its best option, not just the rarer 4×-effective ones.

### If the move will KO the target

This is where Cascade White diverges from vanilla the most. The baseline "guaranteed" bonus is **+4**, same magnitude as vanilla, but *how reliably* that bonus is applied has been reworked per move category:

- **Explosion / Self-Destruct:** no bonus at all, same as vanilla — these already have their own tradeoffs (losing the Pokémon) that the AI shouldn't need extra encouragement for.
- **Sucker Punch / Future Sight** (and, by shared move-effect ID, Doom Desire): route through a shared probabilistic block. **66% of the time (170/256) they get an extra +2 on top of the base +4, for +6 total; the other 34% they still get the standard +4.** They are never denied the KO recognition outright.
  > **Vanilla note — this is a significant fix, not a cosmetic one.** In stock Black/White, this same branch is inverted: a successful 170/256 roll means the move gets **no bonus at all**, and only the 86/256 (~34%) failure case gets the +4. In other words, vanilla's AI recognizes a guaranteed KO with Sucker Punch or Future Sight only about a third of the time — the rest of the time it evaluates the move as if the KO weren't happening. Cascade White's rework guarantees the +4 always applies and adds a *chance of a bonus* on top, rather than a *chance of losing the recognition entirely*.
- **Focus Punch:** no longer part of that probabilistic group at all — it now falls straight through to the guaranteed flat **+4**, with no randomness and no chance at the extra +2. (Vanilla grouped Focus Punch with Sucker Punch/Future Sight under the same unreliable 34%-chance logic described above.)
- **Two-turn/semi-invulnerable moves** (Dive, Dig, Fly, Bounce, Shadow Force) get dedicated handling that didn't exist in vanilla's Script 1 at all:
  - Holding a **Power Herb** (which skips the charge-up turn): guaranteed **+6** (+2, then falls into the standard +4).
  - Without Power Herb: a −2 penalty is applied first (reflecting the extra turn of risk/telegraphing), and then the move still passes through the same 66%/34% roll used by Sucker Punch/Future Sight above — netting **+4** on the 66% success case (the −2 is offset by a +2) or **+2** on the 34% failure case. Either way it never loses KO recognition entirely, it's just discounted relative to a normal attack.
- **Pursuit** gets its own high-confidence bonus, separate from the shared +4 block entirely: an **84.8% (217/256) chance of a flat +7**, otherwise nothing. This isn't present in vanilla's fainting-blow logic at all (vanilla just gives Pursuit the ordinary +4). The AI is now noticeably eager to click a KO-securing Pursuit.
- **Priority moves** (Aqua Jet, Bullet Punch, Extreme Speed, Ice Shard, Mach Punch, Quick Attack, Shadow Sneak, Vacuum Wave) get smarter conditional handling instead of vanilla's unconditional bonus:
  - If the user is slower than *every* opposing Pokémon (i.e. priority is actually needed to secure the KO) **or** a 25% (64/256) random roll succeeds, the move gets a flat **+6** — and that's it; it does *not* additionally receive the shared +4 finisher.
  - Otherwise (user is already faster than everything and the 25% roll fails), the move gets **no KO bonus at all** from this section.
  > **Vanilla note:** stock Black/White always gives priority-move KOs a flat +6 (+2 on top of the standard +4), regardless of whether the user actually needed priority to secure the kill. Cascade White's version reserves the enthusiasm for situations where priority is either needed or, some of the time, just convenient — a Pokémon that's already faster than the whole opposing side doesn't get an artificial nudge toward its priority move over an equally-lethal regular attack.
- Everything else (a normal attacking move that will KO) gets the flat **+4**.

### Multi-battle follow-up bonus

After the KO bonus is applied, if the battle is a Double or Triple Battle, there's a 35% (90/256) chance of an additional **+1** if the move is on a specific curated list of roughly three dozen moves (Blizzard, Rock Slide, Heat Wave, Eruption, Water Spout, Muddy Water, Glaciate, Snarl, Surf, Sludge Wave, Searing Shot, Double-Edge, Iron Tail, Aqua Tail, Cross Chop, Leaf Tornado, Drill Peck, Dragon Rush, Wild Charge, Smog, Power Whip, Attack Order, Take Down, Hyper Voice, Uproar, Electroweb, Icy Wind, Barb Barrage, Air Cutter, Psychic Noise, Dazzling Gleam, Twister, Diamond Storm, Razor Leaf, Low Sweep, Dream Eater, Psywave, Chilling Water, Brine, Solar Beam, Assurance). Worth flagging: this list is **not** simply "all multi-target spread moves" — true spread moves like Surf, Heat Wave, Rock Slide, Muddy Water, and Electroweb are in there, but so are plenty of ordinary single-target moves (Iron Tail, Cross Chop, Drill Peck, Take Down, Psywave...) that have no multi-target mechanic. Since this list was hand-curated in the script rather than derived from a game-data flag, you'll know the intended theme better than an outside read of the bytecode can tell — worth double-checking it still matches what you meant it to if you revisit this section.

This bonus only applies on top of an already-secured KO bonus (it's reached from inside the fainting-blow branch), so it never fires for a move that's merely strong but non-lethal.

---

## Script 2: Expert {#script-2}

This is by far the largest of the five scripts — roughly 6,200 lines in Cascade White's edited version (up from ~4,950 in vanilla) — and it's used by the same "smart" trainers as vanilla (bosses, Ace Trainers, Veterans, etc.). Even DaSquyd's original documentation punts on covering it in detail ("this is the one to look at" is the entire vanilla writeup), and a full line-by-line audit is out of scope here too — this section instead describes the architecture, the consistent design patterns Cascade White applies throughout, and the most notable specific changes found while sampling the file. Treat the script file itself as ground truth for any specific move's exact behavior.

### Architecture

Same shape as Script 0: a single jump table keyed on the move's effect ID, routing to ~150 dedicated handlers (one per distinct move effect, covering everything from stat changes to two-turn moves to ability-altering moves). Where Script 0 asks "would this move accomplish anything at all," Script 2 asks "is *now* a good time to use this, tactically" — its handlers are built almost entirely out of HP percentages, stat-stage thresholds, speed comparisons, and the opponent's last-used-move category, each gating a randomized nudge to the score (rarely more than ±3, occasionally larger for save-or-lose situations like a Pokémon at risk of fainting).

### A new shared toolkit of custom commands

Several handlers in Script 2 call script commands that don't exist in the vanilla instruction set at all — `JumpIfUserWillFaint_Setup`, `JumpIfUserWillTakeLowDamage_Setup`, `JumpIfUserIsSlowerThanAllEnemies`, `JumpIfReservedHasStrongerMove`, and similar. These are Cascade White engine-level additions (not just script-level cleverness) that let the AI reason about "am I about to die" or "would this stat boost even matter before I lose the exchange" directly, instead of approximating it with HP-percentage/speed-comparison heuristics scattered everywhere. The same commands show up again in **Script 3**, which is built around them almost entirely — see below. This is worth knowing about even outside Script 2, since it means the underlying AI has genuinely more tactical awareness available to it in this hack than the vanilla engine ever did, not just more move/ability coverage.

### Recurring design patterns

A few patterns repeat across dozens of handlers, in both vanilla and Cascade White:

- **Self-buffing moves** (Swords Dance, Calm Mind, Bulk Up, etc. — handled per-stat rather than as one generic "setup move" bucket) check the current stat stage, the user's current HP (a full-HP user with Baton Pass on its team gets an extra nudge — "sponsor" the boost for a teammate), and then apply a chance-based small bonus or penalty depending on how "worth it" the boost currently looks.
- **Debuffing moves** (Growl, Leer, etc.) check the target's current stat stage, the target's HP (debuffs matter less against something about to die anyway), and often the category of the opponent's last move — e.g. lowering Defense is deprioritized if the opponent just used a Special move, since it wouldn't matter.
- **Speed-based moves** (Icy Wind, Electroweb, Rock Tomb, and the like) compare current speed order first — if the user is already faster, the value of a further Speed-lowering effect on the opponent is much smaller than if the user is behind and the drop could flip the matchup.
- **Two-turn/charge moves** (Solar Beam, Sky Attack, Skull Bash, Electro Shot's slot, etc.) check for weather that would remove the charge turn (Sun for Solar Beam, Rain for Electro Shot) or a held Power Herb, and penalize the move if neither is present — with an extra-large **-12** if the user is likely to faint before the second turn even happens, via the shared `JumpIfUserWillFaint_Setup` helper.

### Cascade White-specific tactical refinements observed

- **Unaware awareness on stat-raising moves.** Raising Attack or Defense against a target with **Unaware** (which ignores the attacking/defending stat changes of both sides during damage calculation) is now specifically discouraged — vanilla's equivalent handlers have no such check and will happily set up into a wall that will simply ignore it.
- **Category-aware Defense/Sp. Def boosts.** Raising Defense specifically checks whether the opponent's last move was Special (and vice versa for Special Defense) and steeply deprioritizes the "wrong side" boost — a Calm Mind against a physical attacker isn't discouraged by this check, but a Bulk Up against a special attacker's team is.
- **U-Turn/Volt Switch pivot logic** checks whether a reserve party member has a stronger move against the (soon-to-be-revealed) opposing Pokémon before deciding whether pivoting out is worthwhile, using the shared `JumpIfReservedHasStrongerMove` helper — genuine "would switching help" reasoning rather than a flat bonus/penalty for the move category.
- **Close Combat / Superpower-style self-lowering moves** check both current HP and speed order before committing — if the user is slow and not at high HP, the permanent Defense/Sp. Def drop is judged not worth the risk and the move is discouraged.

### Developer's own in-code notes worth revisiting

The edited script carries a number of inline comments that read like notes-to-self rather than finished documentation, which are worth flagging here since they're easy to lose track of in a 6,000-line file:

- Several sections are explicitly marked **`REDUNDANT`** (Guard Split, Power Split, Telekinesis, Magic Room, Smack Down, Trump Card, Heal Block, Power Trick, Punishment, Snatch, Water Sport, Mud Sport, Imprison, Feint, and a few more) — worth a pass to confirm whether the redundancy is intentional (e.g. the handler is a harmless no-op reached by dead code) or whether logic is genuinely missing.
- One block (immediately before **Charge Moves**, around the old `address_0x2952`) is bracketed by the comments **`THIS CODE IS ORPHANED NOW`** / **`NO ONE USES THIS CODE ABOVE`** — a chunk of Taunt/type-matchup logic that nothing in the current jump table routes to anymore. It's dead code sitting in the file rather than logic that's actively wrong, but it's a candidate for cleanup or for re-wiring if it was meant to still be reachable.
- **Dig/Dive** and **Captivate** are marked **`MODIFY`**, and Power Trick's neighborhood has a **`SOMETHING? NOT SURE`** comment — these read as open questions you left for yourself, not settled behavior.
- **Hi Jump Kick** has a bare `//   HI JUMP KICK?` header with a question mark, suggesting the effect-ID mapping into that handler may be worth double-checking against the current move data.

---

## Script 3: StatusDecisions {#script-3}

Script 3 has no vanilla equivalent at all — Black/White's Script 3 ("Status") is the unused, unremarkable first-turn stat-move bonus described in `Gen5EnemyAI.md`. Cascade White repurposes the slot entirely for a purpose-built status/setup-move evaluator, and it's the clearest illustration of the custom "threat assessment" toolkit mentioned above (`JumpIfUserWillFaint_Setup`, `JumpIfUserWillTakeLowDamage_Setup`, `JumpIfUserWillFaint_Priority`, `JumpIfUserIsSlowerThanAllEnemies`, `JumpIfUserAboutToWakeUp`, `CheckOwnDamageIntoAlly`) — every one of them is a Cascade White engine addition, not a vanilla command.

### Dev-testing scaffolding at the top (dead code, but worth knowing about)

The very first block of the script is a chain of labels literally named `TestingFunction1` through `TestingFunction7`, each calling one of the new custom commands and then falling straight through to the next:

```
GetAbilityGuess(attacker)
GetLastPreviousCategory()
TestingFunction1:
    JumpIfUserWillFaint_Setup(&TestingFunction2)
TestingFunction2:
    JumpIfUserWillTakeLowDamage_Setup(&TestingFunction3)
...
TestingFunction7: 
    CheckOwnDamageIntoAlly(&NotTesting)
```

Every one of these conditional jumps points at the very next label in the file, so whether the condition is true or false the script ends up at `NotTesting` regardless — this chain has **no effect on scoring**, it just calls each custom command once per evaluation (presumably to confirm each one worked correctly during development) without ever branching on the result. There's a commented-out line right above it, `// Jump(&NotTesting)`, which looks like it was meant to skip this block entirely once testing was done — it's currently inactive, so the block still runs (harmlessly) every time the script is invoked. Functionally inert, but worth cleaning up or re-enabling that skip if you want one fewer thing to think about when reading this script.

### Real logic starts at `NotTesting`

1. If the target is an ally, end immediately (same convention as the other scripts).
2. **Substitute pre-check:** if the move is on a specific list of mostly-status moves that a Substitute blocks (`substituteBlockedMoves` — stat-drops, status conditions, Gastro Acid, Curse, trapping moves, etc.) *and* the target currently has a Substitute up, the move is deprioritized by **-10** before any further logic runs. The list carries a `// MAY NEED TO UPDATE THIS LIST` comment from you — worth revisiting if you've added new status moves since writing it, since anything missing from this list won't get the Substitute check at all.
3. The move is then classified into one of five buckets (each backed by an explicit move list at the bottom of the script) plus a separate priority-move check:

| Bucket | Moves | Handler behavior |
| --- | --- | --- |
| `setup_moves` | Swords Dance, Growth, Nasty Plot, Calm Mind, Work Up, Howl, Acupressure, Hone Claws, Meditate, Focus Energy, Amnesia, Iron Defense, Cosmic Power, Cotton Guard, Stockpile, Bulk Up, Belly Drum, Coil, Barrier, Acid Armor, Defend Order, Defense Curl, Harden, Minimize, Tail Glow | Deprioritize (**-10**) if the user would faint to the opponent's attack before getting to use the boost; if the user would only take *low* damage anyway (i.e. setting up is safe), a 50% chance of **+2**. |
| `setup_moves_speed` | Victory Dance, Quiver Dance, Dragon Dance, Double Team, Flame Charge, Shift Gear, Shell Smash, Agility, Rock Polish, Autotomize, Tailwind | Routed to the exact same handler as `setup_moves` above — currently no behavioral difference between the two buckets despite being tracked separately. Worth deciding whether Speed-boosting setup should eventually get its own logic (e.g. weighing "I'm slow but this fixes that" more favorably) or whether keeping them merged is intentional. |
| `debuff_moves` | Fake Tears, Screech, Leer, Scary Face, String Shot, Sweet Scent, Tail Whip, Metal Sound | Deprioritize by 2 with a ~80% (204/256) chance if the user would faint to a priority-aware threat check, and likewise if the user would only take low damage anyway (the move isn't urgently needed for survival). |
| `debuff_moves_save` | Charm, Captivate, Confide, Growl, Tickle, Smokescreen, Sand Attack, Eerie Impulse, Feather Dance | Same low-damage check as `debuff_moves`, but first adds a speed/Prankster gate: unless the user has **Prankster** or is already faster than the opponent, there's a ~40% (102/256) chance of an extra **-1** — reflecting that a slow non-Prankster user might simply get hit before the debuff matters. |
| `debuff_moves_status` | Confuse Ray, Supersonic, Swagger, Flatter, Teeter Dance, Attract | Same Prankster/speed gate as `debuff_moves_save`, but on failure it's a straight ~40% chance of **-2** with no separate low-damage check. |

The `debuff_moves` bucket doesn't get the Prankster/speed gate the other two debuff buckets do — if that's intentional (e.g. because those particular moves are usually held by fast users already) that's fine, but it's an asymmetry worth double-checking if you didn't mean for stat-drops and status-inducing debuffs to be treated differently here.

### Priority-move handling

Moves with the priority effect, plus Fake Out and First Impression specifically, get routed to a dedicated `address_Priority` block instead of any of the buckets above:

- If the user would faint even accounting for its priority move (`JumpIfUserWillFaint_Priority`), no bonus — going first doesn't save you if the KO happens anyway.
- If the user is **not** slower than every opponent (i.e. it doesn't actually need priority to go first), no bonus either — priority isn't being wasted encouraging a move the AI would want to use anyway for other reasons.
- Otherwise (the user is genuinely outsped and priority matters): if the move would deal no damage, deprioritize by **-10**. If it's Fake Out or First Impression specifically, check whether this is the user's first turn on the field — if not, **-10** (both moves fail outside their intended window); if so, a guaranteed flat **+15**. Any other priority attack gets a 61% (156/256) chance at the same flat **+15**.

A flat +15 is a very large nudge relative to the rest of these scripts' typical ±1-to-±4 range — this script is clearly designed to make "I'm slower and about to lose the exchange, but I have priority" a strongly preferred line of play, considerably more assertively than vanilla Script 1's +6 priority-KO bonus (see Script 1 above) or the base engine's plain scoring ever did.

---

## Script 7: Doubles {#script-7}

Used by every Double/Triple Battle trainer, plus wild double encounters (as the only active flag — see `Gen5EnemyAI.md` Part VI.II for how flags map to trainers). This script is what makes multi-battle AI aware that a second friendly Pokémon exists on the field at all: everything above (Scripts 0-3) evaluates a move in isolation against a single target, and it's Script 7 that layers "...but would this also hit my ally, and should I care" on top. Cascade White keeps vanilla's overall skeleton — gate on battle style, skip pure single-target-vs-target scoring for spread-vs-opposing-side effectiveness, then a large per-move/per-type table of ally-awareness checks — but roughly triples the table's coverage and adds an entirely new capability: deliberately targeting your *own* ally with support-flavored status moves.

### Baseline gate and opposing-side scoring

If the target is an ally, control jumps straight to ally-specific handling (see below) — the ordinary effectiveness/KO scoring never touches ally targets. Against the opposing side, the shape mirrors Script 1's mini fainting/effectiveness reward structure but scaled down for the doubles context: a move that's only 1/2× or 1/4× effective against its target gets a small chance-based penalty (**-1** / **-2**) unless it would faint the target or the target's ally is already dead (no point being cautious about overkill against a nearly-empty side), and a move that's the "strongest" option gets a further chance at a small bonus if it's super or quadruple effective, or if it's priority.

### Field-effect and weather ally-synergy

Rain Dance, Sunny Day, Hail, Sandstorm, Gravity, Trick Room, and (for a couple of specific ability interactions) Discharge/Surf/Lava Plume-style spread moves all check both the user's own ability and the ally's ability/type before deciding how enthusiastic to be — e.g. Rain Dance gets a bonus if either Pokémon has Hydration/Dry Skin/Swift Swim to benefit from the rain, Trick Room's value is evaluated against the *whole* current turn order (not just the user vs. one opponent) since it can help or hurt every Pokémon on the field simultaneously. This category is conceptually the same as vanilla's equivalent handlers (which already checked things like Leaf Guard/Flower Gift/Solar Power/Sand Veil for Sunny Day/Sandstorm) — Cascade White's version is functionally consistent with that pattern, just re-labeled.

### Elemental "should I hit my own ally" logic — significantly expanded

Vanilla Script 7 covers exactly three cases where the AI might deliberately let a spread move hit its own ally because the ally would actually benefit (or at least not mind): Electric, Fire, and Water-type spread moves checked against the ally's immunity/absorb abilities. Cascade White generalizes this into a much larger, more systematic pattern covering **Electric, Water, Fire, Normal, Grass, and Dark**-type moves, plus type-changing abilities:

- **Discharge / Parabolic Charge, Surf-family, and Lava Plume/heat-wave-family moves** each check the *opposing* ally for an immunity/absorb ability first (Lightning Rod, Motor Drive, Thunder Armor, Volt Absorb / Storm Drain, Water Absorb, Dry Skin / Flash Fire, Well-Baked Body) — if the enemy's ally has one, the move is discouraged, since it'd be feeding the wrong side a benefit.
- Then it checks the **user's own ally** for the same abilities — if the ally would benefit, or has one of a curated set of "doesn't mind being hit" abilities (**Healer, Friend Guard, Forewarn, Plus, Minus**), there's a good chance of a bonus (usually **+3**, sometimes **-8** discouraged instead if the check comes out the other way — read the specific handler if you need the exact branch, the pattern varies slightly per move).
- **Normal-type moves** get a dedicated Boomburst check, plus new awareness of **Galvanize** and **Moisturize** (abilities that change a Normal move's type to Electric or Water respectively) — if the user has one of these, moves like Uproar, Take Down, Double-Edge, Hyper Voice, and Swift are re-evaluated as if they were Electric/Water spread moves for ally-synergy purposes, correctly following the type change through to the ally-immunity logic.
- **Dark-type moves** check the ally for **Justified** (Dark-move-triggered Attack boost) using the shared `CheckOwnDamageIntoAlly` helper.
- A dedicated **Weakness Policy** trigger check exists separately from the ability-based logic above: if a spread move would be super or quadruple effective against the user's own ally, and the ally can absorb the hit safely (via `JumpIfUserWillFaint_Priority` against the ally, i.e. it wouldn't actually faint them), there's a chance of a bonus for deliberately triggering the ally's Weakness Policy.
- Throughout this whole category, the same "can this ability check even be trusted" gate from Script 0 reappears: **Mold Breaker / Turboblaze / Teravolt** on the user, or a held **Ability Drill / Tera Drill**, disables the "would this help the target" assumption for a defending ability, since the user's own move would just punch through it anyway.
- The baseline penalty for targeting your ally with a damaging move that doesn't fit any of the above cases is a hefty flat **-30**, so none of this makes the AI reckless about friendly fire — it only overrides the default when there's a specific, concrete payoff.

### New: using status moves *on your own ally* for their benefit

This is the single largest addition in Script 7 and has no vanilla equivalent at all — vanilla's doubles AI only ever considers hitting an ally with a *damaging* move for an immunity payoff. Cascade White adds a dedicated table of non-damaging moves the AI will consider redirecting at its own ally on purpose:

- **Skill Swap → ally:** gives the ally Levitate if the ally is weak to Ground-type moves (scaled by how bad that weakness is — full immunity types get discouraged, 4×-weak types like Electric/Steel/Poison/Fire/Rock get a solid **+3**), or gives the ally an accuracy-related ability (Keen Senses / No Guard) if the ally is carrying a signature low-accuracy, high-power move (Fire Blast, Thunder, Hydro Pump, Focus Blast, Dynamic Punch, Blizzard, Zap Cannon, Megahorn, Gunk Shot, Magma Storm, Power Whip, Seed Flare, Hurricane, Inferno, or any OHKO move).
- **Entrainment → ally:** checks the ally's *current* ability and the user's *own* ability against two curated lists — a primary "great abilities" list (Speed Boost, Intimidate, Huge Power, Fur Coat, Anticipation, Cursed Body, Moody, Plus, Minus, Aftermath, Permafrost, Friend Guard) and a secondary weather/terrain-synergy list (Solar Power, Dry Skin, Motor Drive, Rain Dish, Chlorophyll, Swift Swim, Ice Body, Sand Rush, Sand Veil, Snow Cloak) — and, provided the user's ability is on one of these lists and giving it to the ally wouldn't put the ally in KO range this turn, has a chance to hand its own good ability over.
- **Swagger / Flatter → ally:** deliberately confuses your own ally in exchange for the Attack (Swagger) or Sp. Atk (Flatter) boost, but only when the confusion risk is actually neutralized — the ally is Psychic-type, holding a Persim/Lum Berry, or protected by Safeguard/Mist — and only when the relevant stat (Attack for Swagger, Sp. Atk for Flatter) is the ally's stronger offensive stat in the first place.
- **Gastro Acid → ally:** strips the ally's *own* ability when that ability is actively harmful to them (**Truant** or **Slow Start**), for a solid **+5** — turning what's normally a purely offensive disruption move into ally support.
- **Agility / Acupressure / Helping Hand → ally:** redirected versions of these normally-self-targeting or general-support moves, gated on the ally not already being maxed out on the relevant stat(s) and (for Agility) the user not already being faster than the field.
- Everything not covered by one of the above still defaults to the same heavy **-30** discouragement against targeting an ally with a status move, so this system only kicks in for the specific curated cases above — it's a deliberate whitelist of "moves I trust the AI to use supportively," not a general "figure out if this status move would help my ally" reasoner.
