# `Enemy AI in Gen V Pokémon`

# `DaSquyd’s Enemy AI in Gen V Pokémon:` `A Complete (WIP) Guide`

## `Last Updated: July 26, 2026 - DaSquyd`

`This document aims to be a complete guide to how the trainer AI functions in the Pokémon Black, White, Black 2, and White 2 Versions, which includes but is not limited to switching out, switching in, move selection, and specific differences between battle styles such as Double Battles and Rotation Battles. This is something of a sequel to a Reddit post I published earlier in my research. While this is specifically for the Gen V games, most of this may still apply to other generations. Please contact me on Discord at DaSquyd for any further questions and suggestions!`

`Before we go any further, let’s get the elephant out of the room. In October of 2024, there was a major leak of Game Freak’s secure repositories and databases that included source code for many Pokémon titles, including Gen V. I want to make it clear that this guide has absolutely nothing to do with those leaks and no information found in this guide was obtained via those leaks. All information contained within this document was already known before the leaks. This document was put together before the leaks even happened. The only edits I’ve made since the leak have been documenting more trainer AI script commands. However, I’ve decided to publish this as a work-in-progress document that I’ll be updating as I get around to it. All of the commands can still be found, fully named, within the scripts themselves anyway, so you shouldn’t get lost when reading them.`

`For the script files themselves that contain all detailed logic, click here! For information on what all the commands do in the scripts, jump down to Script File Command Glossary.`

`I’m also in the process of creating a full list of all move logic for easier searching and understanding here.`

# **`Contributors and Special Thanks`** {#contributors-and-special-thanks}

- `Austin`  
  - `Assistance with move logic documentation`  
- `pyte`  
  - `Discovered a bug in Script 9 (Weather) that causes all non-weather-setting moves to share logic with Sunny Day`  
- `Phoenix107`  
  - `Found a documentation error regarding switch AI given super effective moves`  
- `TrustyPeaches`  
  - `My everything <3`  
  - `Play Cascade White 2!!`  
  - `Identified a bug regarding switch AI and the evaluation of stat changes.`

# **`Contents`** {#contents}

`Contributors and Special Thanks`

[`Contents`](#contents)

[`Part I: Foreword`](#part-i:-foreword)

[`Part II: Using an Item`](#part-ii:-using-an-item)

[`HP-Restoring Items`](#hp-restoring-items)

[`Battle Items`](#battle-items)

[`Status-Curing Items`](#status-curing-items)

[`Other Items`](#other-items)

[`Item Usage Order`](#item-usage-order)

[`Part III: Switching Out`](#part-iii:-switching-out)

[`Perish Song`](#perish-song)

[`Wonder Guard`](#wonder-guard)

[`No Effective Moves`](#no-effective-moves)

[`Choice Item`](#choice-item)

[`Type Immunity Abilities`](#type-immunity-abilities)

[`Natural Cure`](#natural-cure)

[`Type Effectiveness`](#type-effectiveness)

[`Default Switch Pokémon Selection`](#default-switch-pokémon-selection)

[`Part IV: Switching In`](#part-iv:-switching-in)

[`Determining Strongest Move`](#determining-strongest-move)

[`Selecting a Pokémon`](#selecting-a-pokémon)

[`Part V: Rotation`](#part-v:-rotation)

[`Part VI.I: Move Selection Style`](#part-vi.i:-move-selection-style)

[`Single Battle`](#single-battle)

[`Double/Triple Battle`](#double/triple-battle)

[`Rotation Battle`](#rotation-battle)

[`Black`](#black)

[`White`](#white)

[`Black 2/White 2`](#black-2/white-2)

[`Part VI.II: Move Selection Flags`](#part-vi.ii:-move-selection-flags)

[`Script 0: No Effect`](#script-0:-no-effect)

[`Storm Drain Bug`](#storm-drain-bug)

[`Soundproof Bug`](#soundproof-bug)

[`Script 1: Evaluate`](#script-1:-evaluate)

[`The 4× Status Move Bug`](#the-4×-status-move-bug)

[`Script 2: Expert`](#script-2:-expert)

[`Script 3: Status`](#script-3:-status)

[`Script 4: Vs Rivals First Battles`](#script-4:-vs-rivals-first-battles)

[`Script 5: Vs N Final Battle`](#script-5:-vs-n-final-battle)

[`Script 6: Baton Pass`](#script-6:-baton-pass)

[`Script 7: Double/Triple Battle`](#script-7:-double/triple-battle)

[`Script 8: HP-Based`](#script-8:-hp-based)

[`Script 9: Weather`](#script-9:-weather)

[`Script 10: Disruption`](#script-10:-disruption)

[`Script 11: Roaming`](#script-11:-roaming)

[`Script 12: Safari`](#script-12:-safari)

[`Script 13: Tutorial`](#script-13:-tutorial)

[`Script File Command Glossary`](#script-file-command-glossary)

[`Parameter Types`](#parameter-types)

[`Integer`](#integer)

[`Percent`](#percent)

[`Label`](#label)

[`Stored`](#stored)

[`Ability`](#ability)

[`Move`](#move)

[`Move Effect`](#move-effect)

[`Position`](#position)

[`Type`](#type)

[`Type Param`](#type-param)

[`Condition`](#condition)

[`Condition Flag`](#condition-flag)

[`Side Condition`](#side-condition)

[`Weather`](#weather)

[`Damage Calc Result`](#damage-calc-result)

[`Comparison Operator`](#comparison-operator)

[`0x00 - JumpIfRandLT`](#0x00---jumpifrandlt)

[`0x01 - JumpIfRandGT`](#0x01---jumpifrandgt)

[`0x02 - JumpIfRandEQ`](#0x02---jumpifrandeq)

[`0x03 - JumpIfRandNE`](#0x03---jumpifrandne)

[`0x04 - AddToScore`](#0x04---addtoscore)

[`0x05 - JumpIfHealthLT`](#0x05---jumpifhealthlt)

[`0x06 - JumpIfHealthGT`](#0x06---jumpifhealthgt)

[`0x07 - JumpIfHealthEQ`](#0x07---jumpifhealtheq)

[`0x08 - JumpIfHealthNE`](#0x08---jumpifhealthne)

[`0x09 - JumpIfHasAnyStatus`](#0x09---jumpifhasanystatus)

[`0x0A - JumpIfHasNoStatus`](#0x0a---jumpifhasnostatus)

[`0x0B - JumpIfHasCondition`](#0x0b---jumpifhascondition)

[`0x0C - JumpIfNotCondition`](#0x0c---jumpifnotcondition)

[`0x0D - JumpIfBadlyPoisoned`](#0x0d---jumpifbadlypoisoned)

[`0x0E - JumpIfNotBadlyPoisoned`](#0x0e---jumpifnotbadlypoisoned)

[`0x0F - JumpIfHasConditionFlag`](#0x0f---jumpifhasconditionflag)

[`0x10 - JumpIfNotConditionFlag`](#0x10---jumpifnotconditionflag)

[`0x11 - JumpIfHasSideCondition`](#0x11---jumpifhassidecondition)

[`0x12 - JumpIfNotSideCondition`](#0x12---jumpifnotsidecondition)

[`0x13 - JumpIfStoredLT`](#0x13---jumpifstoredlt)

[`0x14 - JumpIfStoredGT`](#0x14---jumpifstoredgt)

[`0x15 - JumpIfStoredEQ`](#0x15---jumpifstoredeq)

[`0x16 - JumpIfStoredNE`](#0x16---jumpifstoredne)

[`0x17 - JumpIfStoredAND`](#0x17---jumpifstoredand)

[`0x18 - JumpIfStoredNAND`](#0x18---jumpifstorednand)

[`0x19 - JumpIfMoveEQ`](#0x19---jumpifmoveeq)

[`0x1A - JumpIfMoveNE`](#0x1a---jumpifmovene)

[`0x1B - JumpIfStoredIsInList`](#0x1b---jumpifstoredisinlist)

[`0x1C - JumpIfStoredIsNotInList`](#0x1c---jumpifstoredisnotinlist)

[`0x1D - JumpIfHasDamagingMove`](#0x1d---jumpifhasdamagingmove)

[`0x1E - JumpIfHasNoDamagingMove`](#0x1e---jumpifhasnodamagingmove)

[`0x1F - GetTurnCount`](#0x1f---getturncount)

[`0x20 - GetType`](#0x20---gettype)

[`0x21 - GetMoveBasePower`](#0x21---getmovebasepower)

[`0x22 - GetCalcMoveDamage`](#0x22---getcalcmovedamage)

[`0x23 - GetPreviousMove`](#0x23---getpreviousmove)

[`0x24 - JumpIfStoredEQ (Duplicate)`](#0x24---jumpifstoredeq-\(duplicate\))

[`0x25 - JumpIfStoredNE (Duplicate)`](#0x25---jumpifstoredne-\(duplicate\))

[`0x26 - JumpCompareSpeed`](#0x26---jumpcomparespeed)

[`0x27 - GetPartyReserveCount`](#0x27---getpartyreservecount)

[`0x28 - GetMove`](#0x28---getmove)

[`0x29 - GetMoveEffect`](#0x29---getmoveeffect)

[`0x2A - GetAbilityGuess`](#0x2a---getabilityguess)

[`Ability Storage Bug`](#ability-storage-bug)

[`0x2B -`](#0x2b--)

# **`Part I: Foreword`** {#part-i:-foreword}

`It should be noted that the AI is effectively the same between wild Pokémon and trainers at a fundamental level. The difference ends up being what actions are available to be chosen and which AI flags are enabled. The following parts will cover things primarily from the perspective of trainers due to the additional complexity.`

# **`Part II: Using an Item`** {#part-ii:-using-an-item}

`We’ll be tackling the concepts in the order that the AI would be determining its actions, and the very first thing Trainer AI does at the beginning of the turn is decide whether or not they want to use an item on their Pokémon, assuming Embargo isn’t currently active on it. Trainers can have up to four items in their bag to use. They’ll go through their available items in order, evaluating each and selecting the first that matches the requirements for usage.`

## `HP-Restoring Items` {#hp-restoring-items}

`If the item restores HP, they’ll select it if the Pokémon is at 25% HP or less. If they have below 12 pixels remaining in the HP bar UI, that guarantees they’re below 25% and will use a healing item if available.`

## `Battle Items` {#battle-items}

`If the item is a battle item (X Attack, X Defense, etc.), it will select the item if the Pokémon can raise the respective stat. For example, it won’t use an X Speed if the Pokémon’s Speed stat is already at +6.`

## `Status-Curing Items` {#status-curing-items}

`If the item cures a status, it will select it if the Pokémon currently has the status that would be cured.`

## `Other Items` {#other-items}

`If the item is anything else, the trainer AI will ignore it completely.`

## `Item Usage Order` {#item-usage-order}

`The trainer AI will check each of their Pokémon from right to left. This means that in double/triple battles where multiple enemy Pokémon are in heal range, the right-most Pokémon will always have priority. The only case where this is not true is if the Pokémon in question is currently semi-invulnerable.`

# **`Part III: Switching Out`** {#part-iii:-switching-out}

`Switching out applies to all battle types besides wild battles. The first thing the AI does here is check to see if the Pokémon can switch out in the first place. Effects from moves like Block or Whirlpool or abilities like Shadow Tag can prevent a Pokémon from switching. Naturally, there needs to be at least one Pokémon in the back of the party that the AI isn’t already switching into. If the Pokémon can switch and has an available Pokémon to switch with, we can continue. Otherwise, we can just exit this section.`

`The AI will select randomly between all adjacent foes (the player’s Pokémon) and use that Pokémon for any of the further evaluations. Because it’s specifically adjacent foes, in a triple battle, the trainer AI will never use the player’s Pokémon on the far left of the field when determining if their Pokémon on the far right of the field should switch out.`

`It should be noted here, and this will come up again, that the AI does get completely fooled by the ability Illusion. When using one of the foe Pokémon to evaluate if they should switch, they will see it as the Pokémon it’s disguised as if it does have Illusion active.`

`From here, it will choose to switch if any of the following cases are true. Only one needs to pass`

## `Perish Song` {#perish-song}

`If the Pokémon is on its final turn of Perish Song, it will always switch out if it can.`

## `Wonder Guard` {#wonder-guard}

`This only applies to Single Battles and if the opposing Pokémon has Wonder Guard. This technically isn’t “guessed” like other ability-checking operations. It shouldn’t matter anyway because the ability is exclusive to Shedinja and it’s the only ability it can have. The trainer AI has a 2/3 chance to switch out if the trainer AI’s Pokémon has no super effective moves against the target and it has a Pokémon in the party who has a super effective move.`

## `No Effective Moves` {#no-effective-moves}

`This only applies if the trainer AI’s Pokémon has no moves capable of hitting the randomly selected target due exclusively to type effectiveness and has at least two damaging moves. This is ignored if the Pokémon has only one or zero damaging moves. And yes, because it’s exclusively type effectiveness, abilities like Storm Drain and Flash Fire are ignored here, too. Those are handled separately.`

`The trainer AI has a 2/3 chance to switch if there is a Pokémon in the party it can switch with that has a super effective move against the randomly selected target. If not, it has a 1/2 chance to switch if at least one Pokémon in the party has a neutrally effective move.`

## `Choice Item` {#choice-item}

`This only applies if the Pokémon’s held item is a Choice Band, Choice Specs, or Choice Scarf and has already been locked into a single move. If the move is non-damaging, there will be a 1/2 chance to switch. If the move is damaging, we only care if it has no effect against the randomly selected target. Once again, this is just type; no abilities are considered. This is ignored if it can do any damage based on type effectiveness.`

`Otherwise, if it has no moves that are effective against the target, it will perform similar checks to the above section: a 2/3 chance if there’s a party Pokémon with a super effective move and a 1/2 chance otherwise if there’s a party Pokémon with a neutral move. This will be ignored in other cases.`

## `Type Immunity Abilities` {#type-immunity-abilities}

`If the Pokémon has at least one super effective move against the target, there is a 2/3 chance that this whole section gets ignored completely.`

`If it’s the 1/3 chance or the Pokémon has no super effective moves, the trainer AI continues by looking at the damage history. It checks every instance of damage it took during the previous turn and checks to see if the Pokémon was ever hit by a move with a type that could be ignored by the type immunity ability of a Pokémon in the party.`

`If this passes, the trainer AI then has a 1/2 chance of switching for each Pokémon it found that has that immunity in party order. That means that if there are two Pokémon in the party that have Flash Fire and the player last used a Fire-type move against the trainer AI’s Pokémon, it has a 75% chance to switch here. More specifically, that’s a 50% chance that it’ll be the first Pokémon with Flash Fire in the party and a 25% chance that it’ll be the second because we only check for the second if the first failed its 50% chance.`

`The following types and abilities are checked:`

* `Water`  
  * `Water Absorb`  
  * `Storm Drain`  
  * `Dry Skin`  
* `Electric`  
  * `Volt Absorb`  
  * `Motor Drive`  
  * `Lightning Rod`  
* `Grass`  
  * `Overgrow`  
* `Fire`  
  * `Flash Fire`

`Yes, you read that correctly. Overgrow is considered to be an immunity to Grass-type moves by the AI. Presumably, this was intended to be Sap Sipper, but Game Freak messed up and accidentally put it as Overgrow instead. Luckily, this bug is incredibly rare due to Overgrow only being on the Grass-type starter Pokémon, which are exclusive to the rival fights. OK sure, if you want to be pedantic, Boss Trainer Harmon in White Forest during the Black 2/White 2 postgame does have a Torterra, but he leads with it, so it doesn’t really matter anyway since he’s never switching it in unless you force him to switch through other methods and then bait him to switch it back in if the player selected Oshawott as their starter.`

`Because the rival’s starter will have Overgrow if the player chose Oshawott, it means they may see their starter as an option to switch into if the player went for a Grass-type attack on the previous turn. It’s not incredibly likely and probably isn’t even all that beneficial for the player when it happens, but it is possible.`

`There isn’t really a way to leverage this either as the only notable Sap Sipper user is Alder in Black/White, who is a postgame fight technically. It’s just a weird little quirk that I think is funny.`

`One additional thing to note here is that there isn’t a check if the target Pokémon has Mold Breaker, Turboblaze, or Teravolt, which would bypass the immunity. Notably, it also does not cover Levitate, which may have some more applicability.`

## `Natural Cure` {#natural-cure}

`We can ignore this if the Pokémon’s ability is not Natural Cure (or it’s suppressed by Gastro Acid), its current HP below 50%, and it is neither asleep nor frozen.`

`Otherwise, we check the damage history for the last move the Pokémon was hit by to see if there’s a Pokémon in the party who can resist the attack in party order. If so, the trainer AI will select that Pokémon to switch to. Keep in mind that no damage simulation is done here. It’s purely type effectiveness, which once again, doesn’t consider abilities.`

## `Type Effectiveness` {#type-effectiveness}

`This section has a 90% chance of being ignored if the Pokémon has a super effective move it can use against the randomly selected target. Additionally, if the total stat stage changes for the Pokémon (respecting positives and negatives) sum to at least -38, we can ignore this as well. This is likely a bug and they intended to use +4 as the threshold. Shoutout to TrustyPeaches for pointing this one out!`

`Finally, our last blanket ignore case is if the Pokémon did not take damage on the previous turn.`

`From here, the trainer AI iterates over each of the Pokémon in the party that can be switched with and have at least one super effective move against the randomly selected target. If the Pokémon in the party is immune to the type of the last damage, the trainer AI has a 1/2 chance to switch out. If it’s not very effective, the chance is 1/3.`

## `Default Switch Pokémon Selection` {#default-switch-pokémon-selection}

`The cases for Type Immunity Ability, Natural Cure, and Type Effectiveness all provide a Pokémon to switch into. If the passing case is Perish Song, Wonder Guard, No Effective Moves, or Choice Item, the trainer AI will use its standard switch-in AI to decide which Pokémon it will switch into, which we’ll cover next.`

# **`Part IV: Switching In`** {#part-iv:-switching-in}

`This section is a little more well-known than most other sections of this document. After a Pokémon has fainted, used U-turn or Volt Switch, or the trainer AI chose to switch it out with a case that doesn’t provide a switch-in Pokémon (see above the part), the next Pokémon to enter the field is decided using the following method.`

`If a Pokémon is switching in due to a manual switch out, the trainer AI will use the randomly selected target that was chosen for the switch out. Otherwise, it will randomly choose an adjacent foe to be the “target” here for further calculations.`

`The trainer AI will iterate through each of the non-fainted Pokémon in its party and store the strongest move for each Pokémon.`

## `Determining Strongest Move` {#determining-strongest-move}

`To determine the strongest, the trainer AI first eliminates all non-damaging moves. Then it considers all moves with a base power less than 10 to be 60 base power instead. That means variable moves like Gyro Ball or Low Kick will always be seen as 60 base power by the AI in this instance. It then finds the type effectiveness of that move against the target, ignoring all effects from abilities or status; this is purely type effectiveness.`

`It will scale the base power accordingly, truncating the value if necessary when dividing by 2 or 4 for the respective not-very-effective results. For example, it will evaluate the power of Fire Punch, which has a base power of 75, used against Geodude, at 37.`

`The base power of the move is completely unaffected by abilities, items, status conditions, or any other effect the move might have. For example, Acrobatics will always be seen as 55 base power regardless of whether or not the user is holding an item.`

## `Selecting a Pokémon` {#selecting-a-pokémon}

`Using the list of strongest moves, the trainer AI performs a selection sort. This is where things get... weird. See, if you’ve studied computer science, you’d know that selection sort is NOT stable. Stability for sorting algorithms refers to whether or not the order is maintained for equal elements. Selection sort will only guarantee the order for the set of entries that all tie for the optimum value.`

`Why does this matter? Well, typically it really wouldn’t, but there are some very niche cases where they won’t default to party order in the way many might expect them to. First and foremost, there needs to be two or more Pokémon switching in at the same time and on the same turn. Because only the first set of tying entries in the sorted list are guaranteed to be in party index order, any runner-up Pokémon beyond that may be less predictable.`

`For example, consider the following list of strongest moves powers:`

| `Party Index` | `Strongest Move Power` |
| :---: | :---: |
| `3` | `50` |
| `4` | `50` |
| `5` | `100` |
| `6` | `40` |

`Note that we are starting at party index 3, assuming the Pokémon at index 1 and 2 are currently on the field and are in the process of switching out. Here is the result of the selection sort algorithm:`

| `Party Index` | `Strongest Move Power` |
| :---: | :---: |
| `5` | `100` |
| `4` | `50` |
| `3` | `50` |
| `6` | `40` |

`You should notice that while the Pokémon at index 5 is correctly the first Pokémon considered for switching, the second is the Pokémon in index 4 despite 3 having the same strongest move power and an earlier party index. Of course, this is all wildly unpredictable anyway given the trainer AI uses a random foe for its calculations and it’s exclusive to double battles. If there existed any triple battle trainers with a full party of six Pokémon, it could be possible there, too. Once again, this probably has no practical use, but it’s interesting to look at.`

# **`Part V: Rotation`** {#part-v:-rotation}

`This part is exclusive to rotation battles. The Pokémon chosen to attack is decided at complete random. If the trainer has the maximum three Pokémon on the field, they effectively have a 1/3 chance to rotate left, a 1/3 chance to rotate right, and a 1/3 chance to not rotate. If only two Pokémon remain, it’s a 1/2 chance for rotation and 1/2 chance to not rotate.`

`Rotation doesn’t apply to the previously discussed switch-out AI. For example, the AI will NOT rotate a Pokémon in specifically to use an immunity ability.`

`From this point forward, the Pokémon that has been rotated in (or the one already at the front if not rotating) will be used for all calculations.`

# **`Part VI.I: Move Selection Style`** {#part-vi.i:-move-selection-style}

`This is going to be the largest and most in-depth part of this document. Additional details and implementation of moves, abilities, and items will be included after.`

`If the Pokémon is locked into using a specific move due to the use of a two-turn move, we can skip this part. If not, the AI checks to see which moves are available to be used. If none are available due to any reason, Struggle is selected.`

`From here, the trainer AI has some split logic depending on the battle style. They are mostly the same, going through each trainer AI flag and using its associated script to evaluate a move score on the target Pokémon. The score for each move begins at 100 and is increased or decreased additively within the scripts.`

## `Single Battle` {#single-battle}

`The respective script is run for each AI flag, once for each allowed move against the target. If multiple moves tie for the highest score, it will select amongst them randomly.`

## `Double/Triple Battle` {#double/triple-battle}

`This works identically to Single Battles with the exception that each move is checked against each target. This is where things get a little more interesting.`

`Let’s imagine the following scenario and associated move scores:`

* `Player team:`  
  * `![][image1]Gastrodon`  
  * `![][image2]Infernape`  
* `Enemy Team:`  
  * `![][image3]Garchomp`  
    * `Vs ![][image1]Gastrodon`  
      * `Dig: 100			25%`  
      * `Dragon Claw: 100		25%`  
    * `Vs ![][image4]Infernape`  
      * `Dig: 100			50%`  
      * `Dragon Claw: 99		0%`  
  * `![][image5]Exeggcute`  
    * `Vs ![][image1]Gastrodon`  
      * `Giga Drain: 100		50%`  
      * `Psychic: 99		0%`  
    * `Vs ![][image6]Infernape`  
      * `Giga Drain: 99		0%`  
      * `Psychic: 100		50%`

`The AI will randomly select its strongest move for Garchomp vs Gastrodon because it was a tie. Let’s say that’s Dragon Claw. Then, it will decide whether to attack Gastrodon or Infernape, given that they both have a tying “strongest move”, Dragon Claw and Dig respectively. The percent chances are shown above, but to reiterate, that means that ultimately in this position, Garchomp has a 50% chance to attack Infernape with Dig, a 25% chance to attack Gastrodon with Dig, and a 25% chance to attack the Gastrodon with Dragon Claw.`

`For Exeggcute, we can see that despite Giga Drain being 4× effective against Gastrodon, it’s only evaluated at 100, tying it with the strongest move against Infernape. This would be different if Giga Drain were able to faint Gastrodon. In that case, Giga Drain would likely be evaluated at 104 instead. The same can be said for Garchomp. If it sees the KO with Dig on Infernape, it will always select it and never attack Gastrodon.`

`So basically, if you’re looking to game the system here, keep in mind that it’s not easy to bait the AI into attacking a specific Pokémon. The only way to guarantee that in standard cases is if they can faint one of your Pokémon with a move but not the other.`

## `Rotation Battle` {#rotation-battle}

`Contrary to popular belief, Rotation Battles are not completely random. The AI will randomly select one of the player’s Pokémon on the field as the target. The attacker is whichever Pokémon it decided to use in Part V. From there, it calculates the same way as it would in a Single Battle. That means it still selects its moves strategically... Well, assuming the other flags are enabled, at least...`

### `Black` {#black}

* `Driftveil City`  
  * `Motorcyclist Charles		[0, 1, 2]`  
* `Route 7`  
  * `Ace Trainer Elmer		[0, 1, 2]`  
* `Opelucid City - Battle House`  
  * `Ace Trainer Eileen		[0, 1, 2]`  
  * `Ace Trainer Lou			[0, 1, 2]`  
* `Black City`  
  * `Roughneck Johnny			[0]`  
  * `Backpacker Kiyo			[0]`

### `White` {#white}

* `Marvelous Bridge`  
  * `Ace Trainer Glinda		[0, 1, 2]`

### `Black 2/White 2` {#black-2/white-2}

* `Route 5 (B2) or Driftveil City (W2)`  
  * `Motorcyclist Charles		[0, 1, 2]`  
* `Chargestone Cave`  
  * `Ace Trainer Vicki		[0, 1, 2]`  
* `Route 7`  
  * `Youngster Cody			[0]`  
* `Reversal Mountain`  
  * `Black Belt Corey			[0, 1]`  
* `Route 14`  
  * `Ace Trainer Kipp			[0, 1, 2]`  
* `Route 13`  
  * `Pokémon Ranger Daryl		[0, 1, 2]`  
* `Opelucid Gym`  
  * `Veteran Denae			[0, 1, 2]`  
* `Twist Mountain - Inside`  
  * `Veteran Chloris			[0, 1, 2]`  
* `Route 8`  
  * `Parasol Lady Ingrid		[0]`  
* `Route 3`  
  * `School Kid Marsha		[0, 2]`  
* `Route 18`  
  * `Veteran Chester			[0, 1, 2]`  
* `Icirrus City`  
  * `Team Plasma Shadow		[0, 1, 2, 7]`

`Any of the above trainers marked with only Flag 0 are effectively random. Any that have Flag 2 (“Expert”) will actually make their decisions based on what you have. Interestingly, the Icirrus City Team Plasma Shadow fight in the postgame of Black 2/White 2 is a Rotation Battle but it has the flag for Double/Triple Battles. This won’t cause the AI to do anything unexpected, however.`

`While not huge, this does give us some room to pad our odds a little. Of the player’s three Pokémon on the field, the two rotation options could be in range to be KO’d by the least threatening attacks from the opposing side if they were to hit your lead. That way, the AI has a 2/3 chance of selecting one of those two Pokémon as the target and then a guaranteed chance of going for the move that would faint it. Of course, the Pokémon you leave in the front would then have an ability that absorbs the attack or just have a type combination that resists it. This only works for the Rotation Battle trainers with Flag 1 enabled.`

# **`Part VI.II: Move Selection Flags`** {#part-vi.ii:-move-selection-flags}

`I’ve mentioned flags quite a bit so far, so it’s now time to actually dive in. The system allows up to 32 move flags. However, only 14 have data, and only 6 appear on trainers in the main story mode of Black/White and 5 in Black 2/White 2.`

`Most trainers in the game only have Flag 0. Bosses, Ace Trainers, Veterans, etc. also typically have Flags 1 and 2 enabled. Double/triple battle trainers, on top of the previously mentioned flags where applicable, also have Flag 7 enabled.`

`Wild Pokémon encountered in dark grass will also have Flag 7 enabled assuming it is a double battle with no other flags enabled. This means that wild double battle Pokémon may still go for moves that won’t have any effect but will simultaneously be aware of their ally. That leads to them potentially going for attacks that hit their ally if it would activate an ability like Storm Drain or Motor Drive.`

`Because of the general lack of flags for the majority of trainers outside of Flag 0, most trainers who aren't bosses, ace trainers, or veterans are actually very random. They pretty much never care about finishing your Pokémon off when you’re low or setting up or anything. Most trainers just select moves at random so long as the move will at least have an effect.`

`All scripts in their original form can be found here.`

`In a few scripts, the AI guesses your Pokémon’s ability. However, it doesn’t have to guess if the ability was already revealed. However, there is an infamous bug related to this that you should read up on as it is incredibly easy to take advantage of if you so wish.`

## `Script 0: No Effect` {#script-0:-no-effect}

`This script discourages moves that would fail or have no effect, often with a drastic reduction such as -10 or -12. This is based on multiple factors, including type effectiveness and immunities via ability.`

### `Storm Drain Bug` {#storm-drain-bug}

`Another known issue for the AI using Script 0 is that it fails to see Storm Drain as an immunity ability, which can cause it to mindlessly spam Water-type moves into a Pokémon with the ability. This is caused by a misinput where it erroneously checks for Levitate. Luckily, this does occur after the proper Levitate check, so the AI for dealing with that ability functions as intended.`

### `Soundproof Bug` {#soundproof-bug}

`AI using Script 0 fails to prevent the move Hyper Voice from being used into a Pokémon with the ability Soundproof.`

## `Script 1: Evaluate` {#script-1:-evaluate}

`This script is used predominantly by boss trainers.` 

* `If the move faints the target...`  
  * `Increases the score for moves that will faint the target by +4 for most moves or by +6 if the move is one of the following priority moves:`  
    * `Aqua Jet`  
    * `Bullet Punch`  
    * `Extreme Speed`  
    * `Ice Shard`  
    * `Mach Punch`  
    * `Quick Attack`  
    * `Shadow Sneak`  
    * `Vacuum Wave`  
  * `Explosion and Self-Destruct are exempt from this fainting score bonus`  
  * `Focus Punch, Sucker Punch, Future Sight, and Doom Desire only have a ~1/3 (86/256) chance of applying the score increase for fainting`  
* `If the move does NOT faint the target...`  
  * `If the move is the “strongest move”...`  
    * `Explosion, Self-Destruct, Focus Punch, and Sucker Punch have a ~80% (205/256) chance of a score reduction of -2`  
    * `If the move is 4× effective, there is a 68.75% (176/256) chance of a score increase of +2, which can potentially cancel out the previous -2 if applicable`  
  * `If the move is not the “strongest move”...`  
    * `The score receives a decrease of -1`

`The AI obtains the “strongest move” by simulating the user’s attack against the target. This simulation does not bind move event listeners. This means that all moves with variable base power are seen as their displayed value, 0 in the case of “--”. For example, Pin Missile will be evaluated as a 14 base power move (even with Skill Link) and Brine will always be 65 base power. Critical hits are completely disabled for the calculation, so moves that always land critical hits like Frost Breath will be evaluated as only 40. This means that move type changes are ignored as well. For example, Judgment and Weather Ball will always be simulated as Normal-type moves.`

`The actual damage roll produced will always be the lowest roll, at 85% damage, and with no critical hit as stated prior. This means that if the lowest of the 16 possible rolls doesn’t faint the target, the AI won’t see it as a KO move.`

`All other damage formula information is properly used, including effects from abilities and items. Huge Power and Pure Power will double the Attack stat, Normalize will set the move’s type to Normal, gems boost their respective type by 1.5x, burn will halve physical damage, etc.`

`If the target has Illusion active, the simulation will use the Pokémon its disguised as in all calculations.`

`Additionally, the “strongest move” can be a move that has no PP remaining. In such a case, the other moves often end up being selected more randomly because they are being reduced evenly by -1.`

### `The 4× Status Move Bug` {#the-4×-status-move-bug}

`There exists an oversight in this script where all status moves follow the same logic path as the strongest move. Included in this is a check for 4× effectiveness. This means that status moves whose types would be 4× effective against the target have a 68.75% chance of receiving a score increase of +2. For example, if the player has a Ducklett on the field and the opponent has a Pokémon with the move Charge, it will often elect to use Charge at a score of 102 even if it has no Electric-type moves to power up or is already at +6 Sp. Defense.`

## `Script 2: Expert` {#script-2:-expert}

`As the name suggests, this script is used by boss trainers and is the largest script of the bunch. Check the script files. If you’re going to browse any of them, this is the one to look at.`

## `Script 3: Status` {#script-3:-status}

`I haven’t seen this script used anywhere in the main story for either Black/White or Black 2/White 2.`

`On the first turn of battle, the AI has a 68.75% (176/256) chance to raise the score by +2 if the move is one of the following:`

* `Acid Armor`  
* `Acupressure`  
* `Agility`  
* `Amnesia`  
* `Barrier`  
* `Bulk Up`  
* `Camouflage`  
* `Charm`  
* `Conversion`  
* `Cosmic Power`  
* `Cotton Spore`  
* `Curse`  
* `Defend Order`  
* `Defense Curl`  
* `Defog`  
* `Double Team`  
* `Electroweb`  
* `Fake Tears`  
* `Feather Dance`  
* `Flash`  
* `Flatter`  
* `Focus Energy`  
* `Glare`  
* `Growl`  
* `Harden`  
* `Howl`  
* `Imprison`  
* `Ingrain`  
* `Iron Defense`  
* `Kinesis`  
* `Leech Seed`  
* `Leer`  
* `Light Screen`  
* `Low Sweep`  
* `Lucky Chant`  
* `Magnet Rise`  
* `Meditate`  
* `Metal Sound`  
* `Minimize`  
* `Nasty Plot`  
* `Poison Gas`  
* `Poison Powder`  
* `Reflect`  
* `Rock Polish`  
* `Sand Attack`  
* `Scary Face`  
* `Screech`  
* `Sharpen`  
* `SmokeScreen`  
* `String Shot`  
* `Stun Spore`  
* `Substitute`  
* `Swagger`  
* `Sweet Scent`  
* `Swords Dance`  
* `Tail Whip`  
* `Tailwind`  
* `Teeter Dance`  
* `Thunder Wave`  
* `Tickle`  
* `Torment`  
* `Whirlpool`  
* `Will-O-Wisp`  
* `Withdraw`  
* `Yawn`

`Yes, Whirlpool is on this list. I have no idea why. Whirlpool has a different effect ID than some of the other trapping moves to account for its ability to hit through Dive.`

## `Script 4: Vs Rivals First Battles` {#script-4:-vs-rivals-first-battles}

`This is used in the Bianca and Cheren fights in your room at the start of Black/White and for the Hugh fight in Aspertia City at the start of Black 2/White 2.`

`The AI will always go for Tackle on the first turn of battle as opposed to the starter Pokémon’s status move. After that, it depends on the player Pokémon’s HP.`

* `HP is >50%: Tackle has a 1/2 chance of being selected`  
* `HP is >25%: Tackle has a 1/4 chance of being selected`  
* `Otherwise:  Tackle has a 1/8 chance of being selected`

`The intent here is to have the AI throw the fight when it’s winning to allow the player to claim the victory. Of course, that’s hardly a guarantee. The AI can still happen to go for Tackle enough times in a row to win.`

## `Script 5: Vs N Final Battle` {#script-5:-vs-n-final-battle}

`This script is only used in Black/White during the final showdown against N at the end of the main story. All it does is give the scores for Fusion Flare and Fusion Bolt +10 on Reshiram and Zekrom on the first turn of the battle, which effectively guarantees its use.`

`This is interesting because N’s Reshiram/Zekrom is 2 levels higher than the player’s and typically faster. If the player goes for their own Fusion Flare/Bolt, it will end up doing double damage and get its special animation because it went second.`

`That being said, it's still strategically better to go for your super effective move or switch.`

## `Script 6: Baton Pass` {#script-6:-baton-pass}

`I’m not sure if this flag is used anywhere. At least, it’s not used by any main story trainers in either Black/White or Black 2/White 2. Regardless, it does have some interesting behavior worth looking at.`

`If the move is Baton Pass...`

* `Score reduction of -2 if it’s the first turn of battle`  
* `Score increase of +3 if Attack stat is boosted to +3 or higher and exit`  
* `Score increase of +2 if Attack stat is boosted to +2 and exit`  
* `Score increase of +1 if Attack stat is boosted to +1 and exit`  
* `Score increase of +3 if Sp. Atk stat is boosted to +3 or higher and exit`  
* `Score increase of +2 if Sp. Atk stat is boosted to +2 and exit`  
* `Score increase of +1 if Sp. Atk stat is boosted to +1 and exit`

`If the move is NOT Baton Pass...`

* `If the Pokémon does not have Baton Pass as a move, there is a 31.25% (80/256) chance that it exits here`  
* `If the move is Swords Dance, Dragon Dance, Calm Mind, or Nasty Plot...`  
  * `If this is the first turn of battle, the move score receives +5 and then it exits`  
  * `If this is NOT the first turn, the score gets -10 if the Pokémon’s HP is below 60% and +1 otherwise`  
* `If the move is Protect or Detect…`  
  * `Score gets -2 if the user had already used either last turn and +2 otherwise`

`The intent here is to prioritize the aforementioned setup moves and then use Baton Pass after having received the boosts. One thing to note is the ordering of the score increases for Baton Pass. Because all levels of Attack stat boosts are checked before Sp. Atk, it means that if a Pokémon is at +1 Attack and +3 Sp. Atk, they’ll still only get the +1 score increase from Attack rather than the +3.`

## `Script 7: Double/Triple Battle` {#script-7:-double/triple-battle}

`This script is used by all trainers who fight the player in a double or triple battle format as well as wild Pokémon encountered in dark grass assuming the player encountered two Pokémon together. For wild battles, this is the only active flag. Much of the logic is avoiding hitting the ally or intentionally hitting them with moves that would trigger a beneficial ability like Water Absorb or Motor Drive.`

## `Script 8: HP-Based` {#script-8:-hp-based}

`This is another unused script. It reduces the score of moves it sees as unlikely to be effective given certain HP ranges for both the user and the target. If the move is in the list for the respective case, the score has an ~80.47% (206/256) chance to reduce the move’s score by -2. This can happen twice (once for the user’s HP case and once for the target’s). For both, “high” refers to >70% HP, “medium” refers to >30% HP, and “low” is <=30% HP.`

|  | `User` |  |  | `Target` |  |
| ----- | :---: | :---: | :---: | :---: | :---: |
| `Move` | `Low HP` | `Medium HP` | `High HP` | `Low HP` | `Medium HP` |
| `Acid Armor` | `✔` | `✔` |  | `✔` | `✔` |
| `Acupressure` | `✔` |  |  | `✔` | `✔` |
| `Agility` | `✔` | `✔` |  | `✔` | `✔` |
| `Amnesia` | `✔` | `✔` |  | `✔` | `✔` |
| `Barrier` | `✔` | `✔` |  | `✔` | `✔` |
| `Belly Drum` | `✔` | `✔` |  |  |  |
| `Bide` | `✔` | `✔` |  | `✔` |  |
| `Bulk Up` | `✔` | `✔` |  | `✔` | `✔` |
| `Calm Mind` | `✔` | `✔` |  | `✔` | `✔` |
| `Captivate` | `✔` | `✔` |  | `✔` | `✔` |
| `Charm` | `✔` | `✔` |  | `✔` | `✔` |
| `Conversion` | `✔` | `✔` |  | `✔` |  |
| `Conversion 2` | `✔` | `✔` |  | `✔` |  |
| `Cosmic Power` | `✔` | `✔` |  | `✔` | `✔` |
| `Cotton Spore` | `✔` | `✔` |  | `✔` | `✔` |
| `Crush Grip` |  |  |  | `✔` | `✔` |
| `Dark Void` |  |  |  | `✔` |  |
| `Defend Order` | `✔` | `✔` |  | `✔` | `✔` |
| `Destiny Bond` |  |  | `✔` |  |  |
| `Double Team` | `✔` | `✔` |  | `✔` | `✔` |
| `Dragon Dance` | `✔` | `✔` |  | `✔` | `✔` |
| `Endure` |  |  | `✔` |  |  |
| `Electroweb` | `✔` | `✔` |  | `✔` | `✔` |
| `Eruption` | `✔` |  |  |  |  |
| `Explosion` |  | `✔` | `✔` | `✔` |  |
| `Fake Tears` | `✔` | `✔` |  | `✔` | `✔` |
| `Feather Dance` | `✔` | `✔` |  | `✔` | `✔` |
| `Fissure` |  |  |  | `✔` |  |
| `Flail` |  |  | `✔` |  |  |
| `Flash` | `✔` | `✔` |  | `✔` | `✔` |
| `Focus Energy` | `✔` | `✔` |  | `✔` | `✔` |
| `Fury Cutter` |  |  |  | `✔` |  |
| `Glare` |  |  |  | `✔` |  |
| `Grass Whistle` |  |  |  | `✔` |  |
| `Growl` | `✔` | `✔` |  | `✔` | `✔` |
| `Grudge` |  |  | `✔` |  |  |
| `Guillotine` |  |  |  | `✔` |  |
| `Harden` | `✔` | `✔` |  | `✔` | `✔` |
| `Heal Order` |  |  | `✔` |  |  |
| `Healing Wish` |  |  | `✔` |  |  |
| `Horn Drill` |  |  |  | `✔` |  |
| `Howl` | `✔` | `✔` |  | `✔` | `✔` |
| `Hypnosis` |  |  |  | `✔` |  |
| `Iron Defense` | `✔` | `✔` |  | `✔` | `✔` |
| `Kinesis` | `✔` | `✔` |  | `✔` | `✔` |
| `Leer` | `✔` | `✔` |  | `✔` | `✔` |
| `Light Screen` | `✔` | `✔` |  | `✔` |  |
| `Lock-On` | `✔` |  |  | `✔` |  |
| `Lovely Kiss` |  |  |  | `✔` |  |
| `Low Sweep` | `✔` | `✔` |  | `✔` | `✔` |
| `Lucky Chant` |  | `✔` |  |  |  |
| `Lunar Dance` |  |  | `✔` |  |  |
| `Meditate` | `✔` | `✔` |  | `✔` | `✔` |
| `Memento` |  |  | `✔` |  |  |
| `Metal Burst` | `✔` |  |  |  |  |
| `Metal Sound` | `✔` | `✔` |  | `✔` | `✔` |
| `Milk Drink` |  |  | `✔` |  |  |
| `Mind Reader` | `✔` |  |  | `✔` |  |
| `Mirror Coat` | `✔` |  |  |  |  |
| `Mist` | `✔` | `✔` |  |  | `✔` |
| `Morning Sun` |  |  | `✔` |  |  |
| `Nasty Plot` | `✔` | `✔` |  | `✔` | `✔` |
| `Pain Split` |  |  |  | `✔` | `✔` |
| `Perish Song` |  |  |  | `✔` | `✔` |
| `Poison Gas` |  |  |  | `✔` | `✔` |
| `Poison Powder` |  |  |  | `✔` | `✔` |
| `Power Swap` |  | `✔` |  |  |  |
| `Psych Up` | `✔` |  |  | `✔` |  |
| `Rage` | `✔` |  |  |  |  |
| `Recover` |  |  | `✔` |  |  |
| `Rest` |  |  | `✔` |  |  |
| `Rock Polish` | `✔` |  |  | `✔` | `✔` |
| `Roost` |  |  | `✔` |  |  |
| `Safeguard` | `✔` | `✔` |  | `✔` | `✔` |
| `Sand Attack` | `✔` | `✔` |  | `✔` | `✔` |
| `Scary Face` |  | `✔` |  | `✔` | `✔` |
| `Screech` | `✔` | `✔` |  | `✔` | `✔` |
| `Self-Destruct` |  | `✔` | `✔` | `✔` |  |
| `Sharpen` | `✔` | `✔` |  | `✔` | `✔` |
| `Sheer Cold` |  |  |  | `✔` |  |
| `Sing` |  |  |  | `✔` |  |
| `Slack Off` |  |  | `✔` |  |  |
| `Sleep Powder` |  |  |  | `✔` |  |
| `Smokescreen` | `✔` | `✔` |  | `✔` | `✔` |
| `Soft-Boiled` |  |  | `✔` |  |  |
| `Spite` |  |  |  | `✔` |  |
| `Spore` |  |  |  | `✔` |  |
| `String Shot` | `✔` | `✔` |  | `✔` | `✔` |
| `Stun Spore` |  |  |  | `✔` |  |
| `Super Fang` |  |  |  | `✔` |  |
| `Supersonic` |  |  |  | `✔` |  |
| `Swagger` |  |  |  | `✔` |  |
| `Sweet Scent` | `✔` | `✔` |  | `✔` | `✔` |
| `Swords Dance` | `✔` | `✔` |  | `✔` | `✔` |
| `Tail Whip` | `✔` | `✔` |  | `✔` | `✔` |
| `Tickle` | `✔` | `✔` |  | `✔` | `✔` |
| `Toxic` |  |  |  | `✔` |  |
| `Water Spout` | `✔` |  |  |  |  |
| `Will-O-Wisp` |  |  |  | `✔` |  |
| `Withdraw` | `✔` | `✔` |  | `✔` | `✔` |
| `Wring Out` |  |  |  | `✔` | `✔` |

`Most of the reasoning for these should be obvious. The AI would theoretically want to avoid using a move like Rage if it’s at low HP and can't afford to take more hits. Once again, this flag is unused in Gen V as far as I can tell.`

## `Script 9: Weather` {#script-9:-weather}

`This one is also unused. Though, it’s a very simple script. All it does is increase the score by +5 for Rain Dance, Sunny Day, Sandstorm, and Hail if their respective weathers are not currently active on the first turn the user is in the battle.`

`There is a notable bug here, for any of the ROM hack developers reading who wanted to include it. Game Freak had a minor oversight in that there is no unconditional jump after checking if the move is weather-setting. Moves that aren’t weather-setting are unintentionally treated like Sunny Day and will receive the +5 in the same conditions.`

## `Script 10: Disruption` {#script-10:-disruption}

`Once again, this is another unused script. All it does is provide a 1/2 chance of +2 to the score if the move is one of the following:`

* `Attract`  
* `Camouflage`  
* `Captivate`  
* `Charm`  
* `Confuse Ray`  
* `Cotton Spore`  
* `Dark Void`  
* `Defog`  
* `Electroweb`  
* `Embargo`  
* `Encore`  
* `Fake Tears`  
* `Feather Dance`  
* `Flash`  
* `Flatter`  
* `Glare`  
* `Grass Whistle`  
* `Growl`  
* `Hypnosis`  
* `Imprison`  
* `Kinesis`  
* `Knock Off`  
* `Leech Seed`  
* `Leer`  
* `Lovely Kiss`  
* `Low Sweep`  
* `Metal Sound`  
* `Nature Power`  
* `Poison Gas`  
* `Poison Powder`  
* `Psycho Shift`  
* `Sand Attack`  
* `Scary Face`  
* `Screech`  
* `Secret Power`  
* `Sing`  
* `Sleep Powder`  
* `SmokeScreen`  
* `Spikes`  
* `Spite`  
* `Spore`  
* `String Shot`  
* `Stun Spore`  
* `Supersonic`  
* `Swagger`  
* `Sweet Kiss`  
* `Tail Whip`  
* `Teeter Dance`  
* `Thunder Wave`  
* `Tickle`  
* `Torment`  
* `Toxic Spikes`  
* `Will-O-Wisp`  
* `Yawn`

## `Script 11: Roaming` {#script-11:-roaming}

`This script is used by roaming Pokémon. It attempts to run from the fight if the user is not trapped in a binding move like Sand Tomb, if the user is not blocked, and if the target doesn't have Shadow Tag or Arena Trap (unless the user has Levitate or is a Flying-type Pokémon).`

## `Script 12: Safari` {#script-12:-safari}

`This is a vestige from older generations as the Safari Zone does not make an appearance in Gen V. It calls Command 0x3E with a parameter of 2 and then Command 0x3F with a parameter of 61.`

## `Script 13: Tutorial` {#script-13:-tutorial}

`This is theoretically used for the tutorial battle near the start of the game. However, I couldn’t actually find it being loaded anywhere. The script itself seems to make the wild Pokémon always flee when the HP of the target (i.e., the tutor’s Pokémon) is at or below 20%, which shouldn’t really happen ever because the battles are scripted. It may just be a carryover from a previous generation.`

# **`Script File Command Glossary`** {#script-file-command-glossary}

`The .ais script files found here contain a number of commands that can seem somewhat esoteric. This is a full list of commands and their uses.`

## `Parameter Types` {#parameter-types}

### `Integer` {#integer}

* `A whole number value, including negatives where applicable`  
* `Expected range may be specified`

### `Percent` {#percent}

* `A whole number value from 0-100`

### `Label` {#label}

* `A position in the script used either to jump to or as a location for data`

### `Stored` {#stored}

* `The type of the currently stored parameter`  
* `Many commands modify the stored parameter`

### `Ability` {#ability}

* `Examples: ‘ability.lightning_rod’, ‘ability.klutz’`

### `Move` {#move}

* `Examples: ‘move.poison_sting’, ‘move.will-o-wisp’`

### `Move Effect` {#move-effect}

> > > 0. `dmg`  
> > > 1. `target_slp`  
> > > 2. `dmg_target_psn`  
> > > 3. `dmg_target_absorb`  
> > > 4. `dmg_target_brn`  
> > > 5. `dmg_target_frz`  
> > > 6. `dmg_target_par`  
> > > 7. `explosion`  
> > > 8. `dream_eater`  
> > > 9. `mirror_move`  
> > > 10. `user_atk+1`  
> > > 11. `user_def+1`  
> > > 12. `user_spe+1`  
> > > 13. `user_spa+1`  
> > > 14. `user_spd+1`  
> > > 15. `user_acc+1`  
> > > 16. `user_eva+1`  
> > > 17. `no_miss`  
> > > 18. `target_atk-1`  
> > > 19. `target_def-1`  
> > > 20. `target_spe-1`  
> > > 21. `target_spa-1`  
> > > 22. `target_spd-1`  
> > > 23. `target_acc-1`  
> > > 24. `target_eva-1`  
> > > 25. `haze`  
> > > 26. `bide`  
> > > 27. `thrash`  
> > > 28. `force_switch`  
> > > 29. `multi-strike_2-5`  
> > > 30. `conversion`  
> > > 31. `dmg_flinch`  
> > > 32. `heal_50`  
> > > 33. `target_tox`  
> > > 34. `dmg_money`  
> > > 35. `light_screen`  
> > > 36. `tri_attack`  
> > > 37. `rest`  
> > > 38. `ohko`  
> > > 39. `razor_wind`  
> > > 40. `direct_half`  
> > > 41. `direct_40`  
> > > 42. `dmg_trap`  
> > > 43. `increased_crit`  
> > > 44. `multi-strike_2`  
> > > 45. `jump_kick`  
> > > 46. `mist`  
> > > 47. `focus_energy`  
> > > 48. `dmg_recoil_25`  
> > > 49. `target_confusion`  
> > > 50. `user_atk+2`  
> > > 51. `user_def+2`  
> > > 52. `user_spe+2`  
> > > 53. `user_spa+2`  
> > > 54. `user_spd+2`  
> > > 55. `user_acc+2`  
> > > 56. `user_eva+2`  
> > > 57. `transform`  
> > > 58. `target_atk-2`  
> > > 59. `target_def-2`  
> > > 60. `target_spe-2`  
> > > 61. `target_spa-2`  
> > > 62. `target_spd-2`  
> > > 63. `target_acc-2`  
> > > 64. `target_eva-2`  
> > > 65. `reflect`  
> > > 66. `target_psn`  
> > > 67. `target_par`  
> > > 68. `dmg_target_atk-1`  
> > > 69. `dmg_target_def-1`  
> > > 70. `dmg_target_spe-1`  
> > > 71. `dmg_target_spa-1`  
> > > 72. `dmg_target_spd-1`  
> > > 73. `dmg_target_acc-1`  
> > > 74. `dmg_target_eva-1`  
> > > 75. `sky_attack`  
> > > 76. `dmg_target_confuse`  
> > > 77. `twineedle`  
> > > 78. `vital_throw`  
> > > 79. `substitute`  
> > > 80. `recharge`  
> > > 81. `rage`  
> > > 82. `mimic`  
> > > 83. `metronome`  
> > > 84. `leech_seed`  
> > > 85. `splash`  
> > > 86. `disable`  
> > > 87. `direct_level`  
> > > 88. `psywave`  
> > > 89. `counter`  
> > > 90. `encore`  
> > > 91. `pain_split`  
> > > 92. `snore`  
> > > 93. `conversion_2`  
> > > 94. `mind_reader`  
> > > 95. `sketch`  
> > > 96. `unknown_0x0060`  
> > > 97. `sleep_talk`  
> > > 98. `destiny_bond`  
> > > 99. `flail`  
> > > 100. `spite`  
> > > 101. `false_swipe`  
> > > 102. `team_heal`  
> > > 103. `increased_priority`  
> > > 104. `triple_kick`  
> > > 105. `theif`  
> > > 106. `spider_web`  
> > > 107. `nightmare`  
> > > 108. `minimize`  
> > > 109. `curse`  
> > > 110. `unknown_0x006e`  
> > > 111. `protect`  
> > > 112. `spikes`  
> > > 113. `foresight`  
> > > 114. `perish_song`  
> > > 115. `sandstorm`  
> > > 116. `endure`  
> > > 117. `rollout`  
> > > 118. `swagger`  
> > > 119. `fury_cutter`  
> > > 120. `attract`  
> > > 121. `return`  
> > > 122. `present`  
> > > 123. `frustration`  
> > > 124. `safeguard`  
> > > 125. `flame_wheel`  
> > > 126. `magnitude`  
> > > 127. `baton_pass`  
> > > 128. `pursuit`  
> > > 129. `rapid_spin`  
> > > 130. `direct_30`  
> > > 131. `unknown_0x0083`  
> > > 132. `morning_sun`  
> > > 133. `unknown0x0085`  
> > > 134. `unknown0x0086`  
> > > 135. `hidden_power`  
> > > 136. `rain_dance`  
> > > 137. `sunny_day`  
> > > 138. `dmg_user_def+1`  
> > > 139. `dmg_user_atk+1`  
> > > 140. `ancient_power`  
> > > 141. `unknown_0x008d`  
> > > 142. `belly_drum`  
> > > 143. `psych_up`  
> > > 144. `mirror_coat`  
> > > 145. `skull_bash`  
> > > 146. `twister`  
> > > 147. `earthquake`  
> > > 148. `future_sight`  
> > > 149. `gust`  
> > > 150. `stomp`  
> > > 151. `solar_beam`  
> > > 152. `thunder`  
> > > 153. `teleport`  
> > > 154. `beat_up`  
> > > 155. `fly`  
> > > 156. `defense_curl`  
> > > 157. `unknown_0x009d`  
> > > 158. `fake_out`  
> > > 159. `uproar`  
> > > 160. `stockpile`  
> > > 161. `spit_up`  
> > > 162. `swallow`  
> > > 163. `unknown_0x00a3`  
> > > 164. `hail`  
> > > 165. `torment`  
> > > 166. `flatter`  
> > > 167. `will-o-wisp`  
> > > 168. `memento`  
> > > 169. `facade`  
> > > 170. `focus_punch`  
> > > 171. `smelling_salts`  
> > > 172. `follow_me`  
> > > 173. `nature_power`  
> > > 174. `charge_electric`  
> > > 175. `taunt`  
> > > 176. `helping_hand`  
> > > 177. `trick`  
> > > 178. `roleplay`  
> > > 179. `wish`  
> > > 180. `assist`  
> > > 181. `ingrain`  
> > > 182. `dmg_user_atk_def-1`  
> > > 183. `magic_coat`  
> > > 184. `recycle`  
> > > 185. `revenge`  
> > > 186. `brick_break`  
> > > 187. `yawn`  
> > > 188. `knock_off`  
> > > 189. `endeavor`  
> > > 190. `dmg_user_hp_pct`  
> > > 191. `skill_swap`  
> > > 192. `imprison`  
> > > 193. `refresh`  
> > > 194. `grudge`  
> > > 195. `snatch`  
> > > 196. `low_kick`  
> > > 197. `secret_power`  
> > > 198. `dmg_recoil_33`  
> > > 199. `teeter_dance`  
> > > 200. `dmg_target_brn_highcrit`  
> > > 201. `mud_sport`  
> > > 202. `dmg_target_tox`  
> > > 203. `weather_ball`  
> > > 204. `dmg_user_spa-2`  
> > > 205. `target_atk_def-1`  
> > > 206. `user_def_spd+1`  
> > > 207. `sky_uppercut`  
> > > 208. `user_atk_def+1`  
> > > 209. `dmg_target_psn_highcrit`  
> > > 210. `water_sport`  
> > > 211. `user_spa_spd+1`  
> > > 212. `user_atk_spe+1`  
> > > 213. `camouflage`  
> > > 214. `roost`  
> > > 215. `gravity`  
> > > 216. `miracle_eye`  
> > > 217. `wake-up_slap`  
> > > 218. `dmg_user_spe-1`  
> > > 219. `gyro_ball`  
> > > 220. `healing_wish`  
> > > 221. `brine`  
> > > 222. `natural_gift`  
> > > 223. `feint`  
> > > 224. `pluck`  
> > > 225. `tailwind`  
> > > 226. `acupressure`  
> > > 227. `metal_burst`  
> > > 228. `dmg_user_switch`  
> > > 229. `dmg_user_def_spd-1`  
> > > 230. `payback`  
> > > 231. `assurance`  
> > > 232. `embargo`  
> > > 233. `fling`  
> > > 234. `psycho_shift`  
> > > 235. `trump_card`  
> > > 236. `heal_block`  
> > > 237. `dmg_target_hp_pct`  
> > > 238. `power_trick`  
> > > 239. `gastro_acid`  
> > > 240. `lucky_chant`  
> > > 241. `me_first`  
> > > 242. `copycat`  
> > > 243. `power_swap`  
> > > 244. `guard_swap`  
> > > 245. `punishment`  
> > > 246. `last_resort`  
> > > 247. `worry_seed`  
> > > 248. `sucker_punch`  
> > > 249. `toxic_spikes`  
> > > 250. `heart_swap`  
> > > 251. `aqua_ring`  
> > > 252. `magnet_rise`  
> > > 253. `flare_blitz`  
> > > 254. `struggle`  
> > > 255. `dive`  
> > > 256. `dig`  
> > > 257. `surf`  
> > > 258. `defog`  
> > > 259. `trick_room`  
> > > 260. `blizzard`  
> > > 261. `whirlpool`  
> > > 262. `volt_tackle`  
> > > 263. `bounce`  
> > > 264. `unknown_0x0108`  
> > > 265. `captivate`  
> > > 266. `stealth_rock`  
> > > 267. `chatter`  
> > > 268. `judgment`  
> > > 269. `dmg_recoil_50`  
> > > 270. `lunar_dance`  
> > > 271. `dmg_target_spd-2`  
> > > 272. `shadow_force`  
> > > 273. `dmg_target_brn_flinch`  
> > > 274. `dmg_target_frz_flinch`  
> > > 275. `dmg_target_par_flinch`  
> > > 276. `dmg_user_spa+1`  
> > > 277. `user_atk_acc+1`  
> > > 278. `wide_guard`  
> > > 279. `guard_split`  
> > > 280. `power_split`  
> > > 281. `wonder_room`  
> > > 282. `dmg_physical`  
> > > 283. `venoshock`  
> > > 284. `autotomize`  
> > > 285. `telekinesis`  
> > > 286. `magic_room`  
> > > 287. `smack_down`  
> > > 288. `dmg_alwayscrit`  
> > > 289. `flame_burst`  
> > > 290. `user_spa_spd_spe+2`  
> > > 291. `heavy_slam`  
> > > 292. `synchronoise`  
> > > 293. `electro_ball`  
> > > 294. `soak`  
> > > 295. `dmg_user_spe+1`  
> > > 296. `acid_spray`  
> > > 297. `foul_play`  
> > > 298. `simple_beam`  
> > > 299. `entrainment`  
> > > 300. `after_you`  
> > > 301. `round`  
> > > 302. `echoed_voice`  
> > > 303. `chip_away`  
> > > 304. `clear_smog`  
> > > 305. `stored_power`  
> > > 306. `quick_guard`  
> > > 307. `ally_switch`  
> > > 308. `shell_smash`  
> > > 309. `heal_pulse`  
> > > 310. `hex`  
> > > 311. `sky_drop`  
> > > 312. `user_spe+2_atk+1`  
> > > 313. `dmg_force_switch`  
> > > 314. `incinerate`  
> > > 315. `quash`  
> > > 316. `growth`  
> > > 317. `acrobatics`  
> > > 318. `reflect_type`  
> > > 319. `retaliate`  
> > > 320. `final_gambit`  
> > > 321. `user_spa+3`  
> > > 322. `user_atk_def_acc+1`  
> > > 323. `bestow`  
> > > 324. `water_pledge`  
> > > 325. `fire_pledge`  
> > > 326. `grass_pledge`  
> > > 327. `work_up`  
> > > 328. `cotton_guard`  
> > > 329. `relic_song`  
> > > 330. `glaciate`  
> > > 331. `freeze_shock`  
> > > 332. `ice_burn`  
> > > 333. `unknown_0x014d`  
> > > 334. `v-create`  
> > > 335. `fusion_flare`  
> > > 336. `fusion_bolt`  
> > > 337. `hurricane`

### `Position` {#position}

0. `target`  
1. `user`  
2. `target.ally`  
3. `ally`

### `Type` {#type}

0. `type.normal`  
1. `type.fighting`  
2. `type.flying`  
3. `type.poison`  
4. `type.ground`  
5. `type.rock`  
6. `type.bug`  
7. `type.ghost`  
8. `type.steel`  
9. `type.fire`  
10. `type.water`  
11. `type.grass`  
12. `type.electric`  
13. `type.psychic`  
14. `type.ice`  
15. `type.dragon`  
16. `type.dark`  
17. `type.none (Typeless/Struggle)`

### `Type Param` {#type-param}

0. `target.type1`  
1. `user.type1`  
2. `target.type2`  
3. `user.type2`  
4. `move.type (currently considered move)`  
5. `stored_move.type`  
6. `ally.type1`  
7. `target.ally.type1`  
8. `ally.type2`  
9. `target.ally.type2`

### `Condition` {#condition}

0. `cond.none`  
1. `cond.paralysis`  
2. `cond.sleep`  
3. `cond.freeze`  
4. `cond.burn`  
5. `cond.poison`  
6. `cond.confusion`  
7. `cond.infatuation`  
8. `cond.bind`  
9. `cond.nightmare`  
10. `cond.curse`  
11. `cond.taunt`  
12. `cond.torment`  
13. `cond.disable`  
14. `cond.yawn`  
15. `cond.heal_block`  
16. `cond.gastro_acid`  
17. `cond.foresight`  
18. `cond.leech_seed`  
19. `cond.embaro`  
20. `cond.perish_song`  
21. `cond.ingrain`  
22. `cond.block`  
23. `cond.encore`  
24. `cond.roost`  
25. `cond.move_lock`  
26. `cond.charge_lock`  
27. `cond.choice_lock`  
28. `cond.must_hit`  
29. `cond.lock-on`  
30. `cond.floating`  
31. `cond.knocked_down`  
32. `cond.telekinesis`  
33. `cond.sky_drop`  
34. `cond.accuracy_up`  
35. `cond.aqua_ring`

### `Condition Flag` {#condition-flag}

0. `cond_fl.action_done`  
1. `cond_fl.no_switch`  
2. `cond_fl.charge`  
3. `cond_fl.fly`  
4. `cond_fl.dive`  
5. `cond_fl.dig`  
6. `cond_fl.shadow_force`  
7. `cond_fl.defense_curl`  
8. `cond_fl.minimze`  
9. `cond_fl.focus_energy`  
10. `cond_fl.power_trick`  
11. `cond_fl.micle_berry`  
12. `cond_fl.no_action`  
13. `cond_fl.flash_fire`  
14. `Cond_fl.baton_pass`

### `Side Condition` {#side-condition}

0. `side_cond.reflect`  
1. `side_cond.light_screen`  
2. `side_cond.safeguard`  
3. `side_cond.mist`  
4. `side_cond.tailwind`  
5. `side_cond.lucky_chant`  
6. `side_cond.spikes`  
7. `side_cond.toxic_spikes`  
8. `side_cond.stealth_rock`  
9. `side_cond.wide_guard`  
10. `side_cond.quick_guard`  
11. `side_cond.rainbow`  
12. `side_cond.sea_of_fire`  
13. `side_cond.swamp`

### `Weather` {#weather}

0. `weather.none`  
1. `weather.sun`  
2. `weather.rain`  
3. `weather.hail`  
4. `Weather.sand`

### `Damage Calc Result` {#damage-calc-result}

0. `no_damage`  
   * `Status moves or moves with a base power of “--”`  
1. `not_strongest`  
2. `Is_strongest`

### `Comparison Operator` {#comparison-operator}

0. `LT`  
1. `GT`  
2. `EQ`  
3. `AND`  
   * `Bitwise AND`  
4. `NAND`  
   * `Bitwise NOT AND`  
5. `LTE`  
6. `GTE`

## `0x00 - JumpIfRandLT` {#0x00---jumpifrandlt}

`Parameters:`

1. `Value (Integer; 0-255)`  
2. `Label (Label)`

`Generates a random number from 0 to 255 and jumps to Label if it is less than Value.`

## `0x01 - JumpIfRandGT` {#0x01---jumpifrandgt}

`Parameters:`

1. `Value (Integer; 0-255)`  
2. `Label (Label)`

`Generates a random number from 0 to 255 and jumps to Label if it is greater than Value.`

## `0x02 - JumpIfRandEQ` {#0x02---jumpifrandeq}

`Parameters:`

1. `Value (Integer; 0-255)`  
2. `Label (Label)`

`Generates a random number from 0 to 255 and jumps to Label if it equals Value.`

## `0x03 - JumpIfRandNE` {#0x03---jumpifrandne}

`Parameters:`

1. `Value (Integer; 0-255)`  
2. `Label (Label)`

`Generates a random number from 0 to 255 and jumps to Label if it does not equal Value.`

## `0x04 - AddToScore` {#0x04---addtoscore}

`Parameters:`

1. `Value (Integer)`

`Adds Value to the current move’s score against the current target. If this is a negative number, the score will be reduced.`

## `0x05 - JumpIfHealthLT` {#0x05---jumpifhealthlt}

`Parameters:`

1. `Pokémon (Position)`  
2. `Health (Percent)`  
3. `Label (Label)`

`Jumps to Label if the current health percent of Pokémon is less than Health.`

## `0x06 - JumpIfHealthGT` {#0x06---jumpifhealthgt}

`Parameters:`

1. `Pokémon (Position)`  
2. `Health (Percent)`  
3. `Label (Label)`

`Jumps to Label if the current health percent of Pokémon is greater than Health.`

## `0x07 - JumpIfHealthEQ` {#0x07---jumpifhealtheq}

`Parameters:`

1. `Pokémon (Position)`  
2. `Health (Percent)`  
3. `Label (Label)`

`Jumps to Label if the current health percent of Pokémon equals Health.`

## `0x08 - JumpIfHealthNE` {#0x08---jumpifhealthne}

`Parameters:`

1. `Pokémon (Position)`  
2. `Health (Percent)`  
3. `Label (Label)`

`Jumps to Label if the current health percent of Pokémon does not equal Health.`

## `0x09 - JumpIfHasAnyStatus` {#0x09---jumpifhasanystatus}

`Parameters:`

1. `Pokémon (Position)`  
2. `Label (Label)`

`Jumps to Label if Pokémon does not have a non-volatile status (Paralysis, Sleep, Freeze, Burn, or Poison).`

## `0x0A - JumpIfHasNoStatus` {#0x0a---jumpifhasnostatus}

`Parameters:`

1. `Pokémon (Position)`  
2. `Label (Label)`

`Jumps to Label if Pokémon does not have a non-volatile status (Paralysis, Sleep, Freeze, Burn, or Poison).`

## `0x0B - JumpIfHasCondition` {#0x0b---jumpifhascondition}

`Parameters:`

1. `Pokémon (Position)`  
2. `Condition (Condition)`  
3. `Label (Label)`

`Jumps to Label if Pokémon has Condition.`

## `0x0C - JumpIfNotCondition` {#0x0c---jumpifnotcondition}

`Parameters:`

1. `Pokémon (Position)`  
2. `Condition (Condition)`  
3. `Label (Label)`

`Jumps to Label if Pokémon does not have Condition.`

## `0x0D - JumpIfBadlyPoisoned` {#0x0d---jumpifbadlypoisoned}

`Parameters:`

1. `Pokémon (Position)`  
2. `Label (Label)`

`Jumps to Label if Pokémon is badly poisoned.`

## `0x0E - JumpIfNotBadlyPoisoned` {#0x0e---jumpifnotbadlypoisoned}

`Parameters:`

1. `Pokémon (Position)`  
2. `Label (Label)`

`Jumps to Label if Pokémon is not badly poisoned.`

## `0x0F - JumpIfHasConditionFlag` {#0x0f---jumpifhasconditionflag}

`Parameters:`

1. `Pokémon (Position)`  
2. `Flag (Condition Flag)`  
3. `Label (Label)`

`Jumps to Label if Pokémon has Flag.`

## `0x10 - JumpIfNotConditionFlag` {#0x10---jumpifnotconditionflag}

`Parameters:`

1. `Pokémon (Position)`  
2. `Flag (Condition Flag)`  
3. `Label (Label)`

`Jumps to Label if Pokémon does not have Flag.`

## `0x11 - JumpIfHasSideCondition` {#0x11---jumpifhassidecondition}

`Parameters:`

1. `Pokémon (Position)`  
2. `Condition (Side Condition)`  
3. `Label (Label)`

`Jumps to Label if Pokémon’s side has Condition.`

## `0x12 - JumpIfNotSideCondition` {#0x12---jumpifnotsidecondition}

`Parameters:`

1. `Pokémon (Position)`  
2. `Condition (Side Condition)`  
3. `Label (Label)`

`Jumps to Label if Pokémon’s side does not have Condition.`

## `0x13 - JumpIfStoredLT` {#0x13---jumpifstoredlt}

`Parameters:`

1. `Value (Stored)`  
2. `Label (Label)`

`Jumps to Label if the stored parameter is less than Value.`

## `0x14 - JumpIfStoredGT` {#0x14---jumpifstoredgt}

`Parameters:`

1. `Value (Stored)`  
2. `Label (Label)`

`Jumps to Label if the stored parameter is greater than Value.`

## `0x15 - JumpIfStoredEQ` {#0x15---jumpifstoredeq}

`Parameters:`

1. `Value (Stored)`  
2. `Label (Label)`

`Jumps to Label if the stored parameter equals Value.`

## `0x16 - JumpIfStoredNE` {#0x16---jumpifstoredne}

`Parameters:`

1. `Value (Stored)`  
2. `Label (Label)`

`Jumps to Label if the stored parameter does not equal Value.`

## `0x17 - JumpIfStoredAND` {#0x17---jumpifstoredand}

`Parameters:`

1. `Bit Field (Stored)`  
2. `Label (Label)`

`Jumps to Label if the result of a bitwise AND operation between the stored parameter and Bit Field does not equal 0.`

## `0x18 - JumpIfStoredNAND` {#0x18---jumpifstorednand}

`Parameters:`

1. `Bit Field (Stored)`  
2. `Label (Label)`

`Jumps to Label if the result of a bitwise AND operation between the stored parameter and Bit Field equals 0.`

## `0x19 - JumpIfMoveEQ` {#0x19---jumpifmoveeq}

`Parameters:`

1. `Move (Move)`  
2. `Label (Label)`

`Jumps to Label if the considered move equals Move.`

## `0x1A - JumpIfMoveNE` {#0x1a---jumpifmovene}

`Parameters:`

1. `Move (Move)`  
2. `Label (Label)`

`Jumps to Label if the considered move does not equal Move.`

## `0x1B - JumpIfStoredIsInList` {#0x1b---jumpifstoredisinlist}

`Parameters:`

1. `Data Label (Label)`  
2. `Jump Label (Label)`

`Jumps to Jump Label if the stored value is in the list at Data Label.`

## `0x1C - JumpIfStoredIsNotInList` {#0x1c---jumpifstoredisnotinlist}

`Parameters:`

1. `Data Label (Label)`  
2. `Jump Label (Label)`

`Jumps to Jump Label if the stored value is not in the list at Data Label.`

## `0x1D - JumpIfHasDamagingMove` {#0x1d---jumpifhasdamagingmove}

`Parameters:`

1. `Label (Label)`

`Jumps to Label if the considered user has at least one damaging move.`

## `0x1E - JumpIfHasNoDamagingMove` {#0x1e---jumpifhasnodamagingmove}

`Parameters:`

1. `Label (Label)`

`Jumps to Label if the considered user has no damaging moves.`

## `0x1F - GetTurnCount` {#0x1f---getturncount}

`Stores: Integer`

`Stores the battle’s current turn count. This is 0 on the first turn.`

## `0x20 - GetType` {#0x20---gettype}

`Parameters:`

1. `Type Param (Type Param)`

`Stores: Type`

`Stores the type found at Type Param.`

## `0x21 - GetMoveBasePower` {#0x21---getmovebasepower}

`Stores:`

* `Base Power (Integer)`

`Stores the base power of the considered move.`

## `0x22 - GetCalcMoveDamage` {#0x22---getcalcmovedamage}

`Parameters:`

1. `Target (Position)`

`Stores: Damage Calc Result`

`If the move is non-damaging, this will always result as ‘no_damage’. Otherwise, it simulates the damage that would be done against Target with all available moves (regardless of PP). The result will be ‘is_strongest’ if the considered move is stronger than all other moves or ties for strongest. The result will be ‘not_strongest’ otherwise.`

`As mentioned in Flag 1, this simulation does not consider the additional effects of moves. The simulation will never see a critical hit even if it should be guaranteed. All other effects from abilities, items, and status still apply.`

## `0x23 - GetPreviousMove` {#0x23---getpreviousmove}

`Parameters:`

1. `Pokémon (Position)`

`Stores: Move`

`Stores the last move used by Pokémon.`

## `0x24 - JumpIfStoredEQ (Duplicate)` {#0x24---jumpifstoredeq-(duplicate)}

`A duplicate of 0x15. This is a vestige from previous generations where multiple commands were used for different integer sizes.`

## `0x25 - JumpIfStoredNE (Duplicate)` {#0x25---jumpifstoredne-(duplicate)}

`A duplicate of 0x16. This is a vestige from previous generations where multiple functions were used for different integer sizes.`

## `0x26 - JumpCompareSpeed` {#0x26---jumpcomparespeed}

`Parameters:`

1. `Operator (Comparison Operator)`  
2. `Label (Label)`

`Jumps to Label if the considered target's speed compares to the user's speed using the specified comparison operator.`

## `0x27 - GetPartyReserveCount` {#0x27---getpartyreservecount}

`Parameters:`

1. `Pokémon (Position)`

`Stores: Integer`

`Stores the number of non-fainted Pokémon in the party of Pokémon’s trainer. This is only a count of the Pokémon not currently on the field.`

## `0x28 - GetMove` {#0x28---getmove}

`Stores: Move`

`Stores the considered move.`

## `0x29 - GetMoveEffect` {#0x29---getmoveeffect}

`Stores: Move Effect`

`Stores the move effect of the considered move.`

## `0x2A - GetAbilityGuess` {#0x2a---getabilityguess}

`Parameters:`

1. `Pokémon (Position)`

`Stores: Ability`

`Guesses the ability of Pokémon and stores the result. If Pokémon is affected by Gastro Acid, this is always none. If Pokémon is the user or an ally, the true ability will always stored. Otherwise, it first checks to see if the ability is already known.`

`If there is no stored ability, it will then check to see if Pokémon’s true ability is Shadow Tag, Arena Trap, or Magnet Pull. In any of those cases, it will always know. It should be noted that the “known” ability is checked before these, so it will still assume the incorrect revealed ability before it is aware of these. This does not affect the trainer’s desire to switch out in cases where it wants to. This only applies to move selection.`

`In the cases where no ability is stored and the ability is not from the above, it will select randomly between the possible abilities for the species, including the hidden ability if the species has one.`

### `Ability Storage Bug` {#ability-storage-bug}

`There’s an infamous bug here, however, where the known ability is based on the position of the Pokémon rather than the Pokémon itself. So if a Pokémon reveals its ability, the AI will think that any Pokémon in that slot has the last revealed ability until it is replaced by revealing a different one.`

`For example, if the player’s Jolteon reveals its Volt Absorb, the AI will know thereafter. It won’t have to “guess” anymore, and just assume that the Jolteon is immune to Electric-type moves. If the player switches Jolteon out into Mantine, the AI will think that Mantine has Volt Absorb even though it doesn’t. This means that the AI will avoid going for Electric-type moves into that slot, which can be taken advantage of by the player in many fights.`

`The AI will always know their own abilities or the abilities of ally Pokémon. Strangely, it still does store the data for its own slots regardless. The value for each field slot is only cleared if a Pokémon in that slot faints. It will not change for any reason unless a new ability is revealed for that slot. This even includes using a move like Ally Switch.`

## `0x2B -`  {#0x2b--}

# `Moves (WIP)`

# `Moves (WIP)`

# **`Overview`** {#overview}

`This is the page for all move-related AI logic.`

`This is a work-in-progress section! I’ll be adding to this over time.`

`— Love, DaSquyd <3`

`Since Squyd is currently busy with working on Blaze Black and Volt White 2 redux v2, text me on discord if you notice any mistakes.`

`— Also love, Dodominoe (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧`

`For real, thanks for all the help Dodominoe!!`

`– Love, DaSquyd again <3 <3`

# **`Contents`** {#contents-1}

`Overview`

[`Contents`](#contents-1)

[`Move Logic`](#move-logic)

[`Script Overhead`](#script-overhead)

[`Standard Moves`](#standard-moves)

[`Induces Sleep`](#induces-sleep)

[`No Effect (Flag 0)`](#no-effect-\(flag-0\))

[`Expert (Flag 2)`](#expert-\(flag-2\))

[`Draining (0x03)`](#draining-\(0x03\))

[`Expert (Flag 2)`](#expert-\(flag-2\)-1)

[`Self-Destructing`](#self-destructing)

[`No Effect (Flag 0)`](#no-effect-\(flag-0\)-1)

[`Evaluate (Flag 1)`](#evaluate-\(flag-1\))

[`Expert (Flag 2)`](#expert-\(flag-2\)-2)

[`Dream Eater`](#dream-eater)

[`No Effect (Flag 0)`](#no-effect-\(flag-0\)-2)

[`Expert (Flag 2)`](#expert-\(flag-2\)-3)

[`Mirror Move`](#mirror-move)

[`Expert (Flag 2)`](#expert-\(flag-2\)-4)

[`Raise User Attack`](#raise-user-attack)

[`No Effect (Flag 0)`](#no-effect-\(flag-0\)-3)

[`Expert (Flag 2)`](#expert-\(flag-2\)-5)

[`Raise User Defense`](#raise-user-defense)

[`No Effect (Flag 0)`](#no-effect-\(flag-0\)-4)

[`Expert (Flag 2)`](#expert-\(flag-2\)-6)

[`Raise User Speed`](#raise-user-speed)

[`No effect (Flag 0)`](#no-effect-\(flag-0\)-5)

[`Expert (Flag 2)`](#expert-\(flag-2\)-7)

[`Raise User Sp. Atk`](#raise-user-sp. atk)

[`Raise User Sp. Def`](#raise-user-sp. def)

[`Raise User Evasion`](#raise-user-evasion)

[`No Miss`](#no-miss)

[`Lower Target Attack`](#lower-target-attack)

[`Lower Target Defense`](#lower-target-defense)

[`Lower Target Speed`](#lower-target-speed)

[`Lower Target Sp. Def`](#lower-target-sp. def)

[`Lower Target Accuracy`](#lower-target-accuracy)

[`Lower Target Evasion`](#lower-target-evasion)

[`Haze`](#haze)

[`Bide`](#bide)

[`Force Switch`](#force-switch)

[`No Effect (Flag 0)`](#no-effect-\(flag-0\)-6)

[`Expert (Flag 2)`](#expert-\(flag-2\)-8)

[`Conversion`](#conversion)

[`Recover HP`](#recover-hp)

[`Badly Poison Target`](#badly-poison-target)

[`Light Screen`](#light-screen)

[`Expert (Flag 2)`](#expert-\(flag-2\)-9)

[`Rest`](#rest)

[`OHKO`](#ohko)

[`No Effect (Flag 0)`](#no-effect-\(flag-0\)-7)

[`Expert (Flag 2)f`](#expert-\(flag-2\)f)

[`Two-turn (Standard)`](#two-turn-\(standard\))

[`Expert (Flag 2)`](#expert-\(flag-2\)-10)

[`Direct Damage (Half)`](#direct-damage-\(half\))

[`Direct Damage (40 HP)`](#direct-damage-\(40-hp\))

[`Trapping`](#trapping)

[`Expert (Flag 2)`](#expert-\(flag-2\)-11)

[`Increased Critical Hit Ratio`](#increased-critical-hit-ratio)

[`Expert (Flag 2)`](#expert-\(flag-2\)-12)

[`Semi-Invulnerable (Except Shadow Force)`](#semi-invulnerable-\(except-shadow-force\))

[`Expert (Flag 2)`](#expert-\(flag-2\)-13)

[`Focus Punch`](#focus-punch)

[`No Effect (Flag 0)`](#no-effect-\(flag-0\)-8)

[`Evaluate (Flag 1)`](#evaluate-\(flag-1\)-1)

# **`Move Logic`** {#move-logic}

### `Script Overhead` {#script-overhead}

`The “common random” is a value assigned as any integer 0–255 chosen at the start of move selection for each Pokémon. It is occasionally used as a means of randomizing decisions, but unlike standard randomness, this is a consistent value for the entirety of the move selection process.`

- `Effectiveness (Flag 0)`  
  - `Assumes that the target is NOT an ally`  
    - `Score +0`  
  - `Assumes that the move is not 0× effective`  
    - `Score -10`  
  - `Assumes that the move won’t be failing due to an ability (with the exception of Storm Drain due to its related bug)`  
    - `Score -12`  
- `Evaluate (Flag 1)`  
  - `Assumes that the target is NOT an ally`  
    - `Score +0`  
  - `If no logic is specified, assume the following...`  
    - `Score +4 if the move will KO`  
    - `Score -1 if the move is not the strongest`  
    - `Score +2 (68.75%) if the move is the strongest but won’t KO and is 4× effective`

## `Standard Moves` {#standard-moves}

`Let’s get these cleared out of the way first. These are the moves that have no particular AI logic.`

- `#001 Pound`  
- `#003 Double Slap`  
- `#004 Comet Punch`  
- `#005 Mega Punch`  
- `#006 Pay Day`  
- `#007 Fire Punch`  
- `#008 Ice Punch`  
- `#009 Thunder Punch (ThunderPunch)`  
- `#010 Scratch`  
- `#011 Vise Grip (Vice Grip, ViceGrip)`  
- `#015 Cut`  
- `#016 Gust`  
- `#017 Wing Attack`  
- `#021 Slam`  
- `#022 Vine Whip`  
- `#024 Double Kick`  
- `#025 Mega Kick`  
- `#026 Jump Kick`  
- `#027 Rolling Kick`  
- `#029 Headbutt`  
- `#030 Horn Attack`  
- `#031 Fury Attack`  
- `#033 Tackle`  
- `#037 Thrash`  
- `#042 Pin Missile`  
- `#044 Bite`  
- `#055 Water Gun`  
- `#056 Hydro Pump`  
- `#064 Peck`  
- `#065 Drill Peck`  
- `#070 Strength`  
- `#080 Petal Dance`  
- `#088 Rock Throw`  
- `#121 Egg Bomb`  
- `#125 Bone Club`  
- `#127 Waterfall`  
- `#131 Spike Cannon`  
- `#136 High Jump Kick (Hi Jump Kick)`  
- `#140 Barrage`  
- `#154 Fury Swipes`  
- `#155 Bonemerang`  
- `#157 Rock Slide`  
- `#158 Hyper Fang`  
- `#161 Tri Attack`  
- `#198 Bone Rush`  
- `#200 Outrage`  
- `#224 Megahorn`  
- `#292 Arm Thrust`  
- `#304 Hyper Voice`  
- `#310 Astonish`  
- `#326 Extrasensory`  
- `#331 Bullet Seed`  
- `#333 Icicle Spear`  
- `#337 Dragon Claw`  
- `#350 Rock Blast`  
- `#399 Dark Pulse`  
- `#401 Aqua Tail`  
- `#402 Seed Bomb`  
- `#403 Air Slash`  
- `#404 X-Scissor`  
- `#406 Dragon Pulse`  
- `#407 Dragon Rush`  
- `#408 Power Gem`  
- `#428 Zen Headbutt`  
- `#438 Power Whip`  
- `#442 Iron Head`  
- `#458 Double Hit`  
- `#530 Dual Chop`  
- `#531 Heart Stamp`  
- `#541 Tail Slap`  
- `#544 Gear Grind`  
- `#556 Icicle Crash`

## `Induces Sleep` {#induces-sleep}

- `#047 Sing`  
- `#079 Sleep Powder`  
- `#095 Hypnosis`  
- `#142 Lovely Kiss`  
- `#147 Spore`  
- `#320 Grass Whistle`  
- `#464 Dark Void`

  ### `No Effect (Flag 0)` {#no-effect-(flag-0)}

  `![][image7]`

  ### `Expert (Flag 2)` {#expert-(flag-2)}

`![][image8]`

## `Draining (0x03)` {#draining-(0x03)}

- `#071 Absorb`  
- `#072 Mega Drain`  
- `#141 Leech Life`  
- `#202 Giga Drain`  
- `#409 Drain Punch`  
- `#532 Horn Leech`

### `Expert (Flag 2)` {#expert-(flag-2)-1}

`![][image9]`

## `Self-Destructing` {#self-destructing}

- `#120 Self-Destruct`  
- `#153 Explosion`  
- `#262 Memento`

  ### `No Effect (Flag 0)` {#no-effect-(flag-0)-1}

| `Move Effectiveness` | `User has... Mold Breaker` | `Guess target ability` | `Score Change` |
| :---: | :---: | :---: | :---: |
| `0×` |  |  | `-10` |
| `Other` | `TRUE` |  | `See next table...` |
|  | `FALSE` | `Damp` | `-10` |
|  |  | `Other` | `See next table...` |

| `User Team Reserve Count` | `Target Team Reserve Count` | `Score Change` |
| :---: | :---: | :---: |
| `0` | `0` | `-1` |
|  | `1–5` | `-10` |
| `1–5` |  | `+0` |

  ### `Evaluate (Flag 1)` {#evaluate-(flag-1)}

`![][image10]`

`*= 4× type effectiveness is not typically possible with Self-Destruct and Explosion as both are Normal-type moves.`

### `Expert (Flag 2)` {#expert-(flag-2)-2}

`![][image11]`

## `Dream Eater` {#dream-eater}

- `#138 Dream Eater`

### 	`No Effect (Flag 0)` {#no-effect-(flag-0)-2}

	`	![][image12]`

### `Expert (Flag 2)` {#expert-(flag-2)-3}

`![][image13]`

## `Mirror Move` {#mirror-move}

- `#119 Mirror Move`

### `Expert (Flag 2)` {#expert-(flag-2)-4}

`![][image14]`

`The list mentioned in the flowchart contains the following moves:`

- `#012 Guillotine`  
- `#028 Sand Attack`  
- `#032 Horn Drill`  
- `#047 Sing`  
- `#063 Hyper Beam`  
- `#077 Poison Powder`  
- `#079 Sleep Powder`  
- `#086 Thunder Wave`  
- `#090 Fissure`  
- `#092 Toxic`  
- `#095 Hypnosis`  
- `#103 Screech`  
- `#108 Smokescreen`  
- `#109 Confuse Ray`  
- `#137 Glare`  
- `#142 Lovely Kiss`  
- `#147 Spore`  
- `#168 Thief`  
- `#177 Aeroblast`  
- `#178 Cotton Spore`  
- `#184 Scary Face`  
- `#186 Sweet Kiss`  
- `#207 Swagger`  
- `#213 Attract`  
- `#223 Dynamic Punch`  
- `#238 Cross Chop`  
- `#245 Extreme Speed`  
- `#247 Shadow Ball`  
- `#259 Torment`  
- `#260 Flatter`  
- `#271 Trick`  
- `#276 Superpower`  
- `#285 Skill Swap`  
- `#313 Fake Tears`  
- `#319 Metal Sound`  
- `#320 Grass Whistle`  
- `#325 Shadow Punch`  
- `#329 Sheer Cold`  
- `#343 Covet`  
- `#375 Psycho Shift`  
- `#384 Power Swap`  
- `#385 Guard Swap`  
- `#389 Sucker Punch`  
- `#391 Heart Swap`  
- `#415 Switcheroo`  
- `#445 Captivate`  
- `#464 Dark Void`  
- `#549 Glaciate`  
- `#555 Snarl`

## `Raise User Attack` {#raise-user-attack}

- `#014 Swords Dance`  
- `#096 Meditate`  
- `#159 Sharpen`  
- `#336 Howl`

  ### `No Effect (Flag 0)` {#no-effect-(flag-0)-3}

| `User’s Attack Stat Stage` | `Score Change` |
| :---: | :---: |
| `-6 to +5` | `+0` |
| `+6` | `-10` |

  ### `Expert (Flag 2)` {#expert-(flag-2)-5}

| `User’s Attack Stat Stage` | `User’s Current HP` | `User has... Baton Pass` | `Score Change` |
| :---: | :---: | :---: | :---: |
| `-6 to +2` | `1–39.999%` |  | `-2` |
|  | `40–70%` |  | `-2 (84.375%) +0 (15.625%)` |
|  | `70.001–99%` |  | `+0` |
|  |  |  |  |
|  | `100%` | `TRUE` | `+2` |
|  |  | `FALSE` | `+0 (50%) +2 (50%)` |
| `+3 to +6` | `1–39.999%` |  | `-3 (60.9375%) -2 (39.0625%)` |
|  | `40–70%` |  | `-3 (51.4160%) -2 (32.9590%) -1 ( 9.5215%) +0 ( 6.1035%)` |
|  | `70.001–100%` |  | `-1 (60.9375%) +0 (39.0625%)` |

## `Raise User Defense` {#raise-user-defense}

- `#106 Harden`  
- `#110 Withdraw`  
- `#112 Barrier`  
- `#151 Acid Armor`  
- `#334 Iron Defense`

### `No Effect (Flag 0)` {#no-effect-(flag-0)-4}

`![][image15]`

### `Expert (Flag 2)` {#expert-(flag-2)-6}

| `User’s Defense Stat Stage` | `User’s Current HP` | `User has  Baton Pass` | `Target used Move with 0 Power Last Turn` | `Target used Special Move Last Turn` | `Score Change` |
| :---: | :---: | :---: | :---: | :---: | :---: |
| `-6 to +2` | `1–39.99%` |  |  |  | `-2` |
|  | `40–69.99%` |  | `TRUE` |  | `-2 (76.56%) +0 (23.44%)` |
|  |  |  | `FALSE` | `TRUE` | `-2` |
|  |  |  |  | `FALSE` | `-2 (58.62%) +0 (41.38%)` |
|  | `70–99.99%` |  | `TRUE` |  | `-2 (16.75%) +0 (83.25%)` |
|  |  |  | `FALSE` | `TRUE` | `-2 (21.88%) +0 (78.13%)` |
|  |  |  |  | `FALSE` | `-2 (12.82%) +0 (87.18%)` |
|  | `100%` | `TRUE` | `TRUE` |  | `+0 (16.75%) +2 (83.25%)` |
|  |  |  | `FALSE` | `TRUE` | `+0 (21.88%) +2 (78.13%)` |
|  |  |  |  | `FALSE` | `+0 (12.82%) +2 (87.18%)` |
|  |  | `FALSE` | `TRUE` |  | `-2  (8.37%) +0    (50%) +2 (41.63%)` |
|  |  |  | `FALSE` | `TRUE` | `-2 (10.94%) +0    (50%) +2 (39.06%)` |
|  |  |  |  | `FALSE` | `-2  (6.41%) +0    (50%) +2 (43.59%)` |
| `+3 to +6` | `1–39.99%` |  |  |  | `-1 (60.94%) +0 (39.06%)` |
|  | `40–69.99%` |  | `TRUE` |  | `-1 (46.66%) +0 (29.91%) +1 (14.28%) +2  (9.16%)` |
|  |  |  | `FALSE` | `TRUE` | `-1 (60.94%) +0 (39.06%)` |
|  |  |  |  | `FALSE` | `-1 (35.72%) +0  (22.9%) +1 (25.22%) +2 (16.16%)` |
|  | `70–100%` |  | `TRUE` |  | `-1 (10.21%) +0  (6.54%) +1 (50.73%) +2 (32.52%)` |
|  |  |  | `FALSE` | `TRUE` | `-1 (13.33%) +0  (8.54%) +1 (47.61%) +2 (30.52%)` |
|  |  |  |  | `FALSE` | `-1  (7.81%) +0  (5.01%) +1 (53.12%) +2 (34.05%)` |

## 

## `Raise User Speed` {#raise-user-speed}

- `#097 Agility`  
- `#397 Rock Polish`

### `No effect (Flag 0)` {#no-effect-(flag-0)-5}

`![][image16]`

### `Expert (Flag 2)` {#expert-(flag-2)-7}

`![][image17]`

`The list mentioned in the flowchart contains the following moves:`

- `#023 Stomp`  
- `#027 Rolling Kick`  
- `#029 Headbutt`  
- `#044 Bite`  
- `#105 Recover`  
- `#125 Bone Club`  
- `#127 Waterfall`  
- `#135 Soft-Boiled`  
- `#156 Rest`  
- `#157 Rock SLide`  
- `#158 Hyper Fang`  
- `#164 Substitute`  
- `#194 Destiny Bond`  
- `#208 Milk Drink`  
- `#220 Pain Split`  
- `#226 Baton Pass`  
- `#234 Morning Sun`  
- `#235 Synthesis`  
- `#236 Moonlight`  
- `#302 Needle Arm`  
- `#303 Slack Off`  
- `#310 Astonish`  
- `#326 Extrasensory`  
- `#355 Roost`  
- `#399 Dark Pulse`  
- `#403 Air Slash`  
- `#407 Dragon Rush`  
- `#428 Zen Headbutt`  
- `#442 Iron Head`  
- `#456 Heal Order`  
- `#531 Heart Stamp`  
- `#537 Steamroller`  
- `#556 Icicle Crash`

  `Essentially, this includes every healing move except for Heal Pulse and Swallow, every flinching move except for Sky Attack, Snore, Twister, Fake Out and Thunder/Ice/Fire Fang, as well as Substitute, Destiny Bond, Pain Split and Baton Pass.`

## `Raise User Sp. Atk` {#raise-user-sp. atk}

- `#417 Nasty Plot`

## `Raise User Sp. Def` {#raise-user-sp. def}

- `#133 Amnesia`

## `Raise User Evasion` {#raise-user-evasion}

- `#104 Double Team`  
- `#107 Minimize`

## `No Miss` {#no-miss}

- `#129 Swift`  
- `#185 Faint Attack`  
- `#325 Shadow Punch`  
- `#332 Aerial Ace`  
- `#345 Magical Leaf`  
- `#351 Shock Wave`  
- `#396 Aura Sphere`  
- `#443 Magnet Bomb`

## `Lower Target Attack` {#lower-target-attack}

- `#045 Growl`  
- `#204 Charm`  
- `#297 Feather Dance`

## `Lower Target Defense` {#lower-target-defense}

- `#039 Tail Whip`  
- `#043 Leer`  
- `#103 Screech`

## `Lower Target Speed` {#lower-target-speed}

- `#081 String Shot`  
- `#178 Cotton Spore`  
- `#184 Scary Face`  
- `#490 Low Sweep`  
- `#527 Electroweb`

## `Lower Target Sp. Def` {#lower-target-sp. def}

- `#313 Fake Tears`  
- `#319 Metal Sound`

## `Lower Target Accuracy` {#lower-target-accuracy}

- `#028 Sand Attack`  
- `#108 SmokeScreen`  
- `#134 Kinesis`  
- `#148 Flash`

## `Lower Target Evasion` {#lower-target-evasion}

- `#230 Sweet Scent`

## `Haze` {#haze}

- `#114 Haze`

## `Bide` {#bide}

- `#117 Bide`

## `Force Switch` {#force-switch}

- `#018 Whirlwind`  
- `#046 Roar`

  ### `No Effect (Flag 0)` {#no-effect-(flag-0)-6}

| `Target Team Reserve Count` | `User has... Mold Breaker` | `Guess Target’s Ability` | `Score Change` |
| :---: | :---: | :---: | :---: |
| `0` |  |  | `-10` |
| `1–5` | `TRUE` |  | `+0` |
|  | `FALSE` | `Suction Cups` | `-10` |
|  |  | `Magic Bounce` | `-12` |
|  |  | `Other` | `+0` |

  ### `Expert (Flag 2)` {#expert-(flag-2)-8}

| `Target Turn Count` | `Target side has... Spikes, Stealth Rock, and/or Toxic Spikes` | `Target’s Attack, Defense, Sp. Atk, Sp. Def, and/or evasion stat is... +3 – +6` | `Score Change` |
| :---: | :---: | :---: | :---: |
| `0–3` | `TRUE` |  | `+0 (50%) +2 (50%)` |
|  | `FALSE` | `TRUE` | `+0 (50%) +2 (50%)` |
|  |  | `FALSE` | `-3` |
| `4+` |  |  | `+0 (12.5%) +2 (50.0%) +4 (37.5%)` |

## `Conversion` {#conversion}

- `#160 Conversion`

## `Recover HP` {#recover-hp}

- `#105 Recover`  
- `#135 Softboiled`  
- `#208 Milk Drink`  
- `#303 Slack Off`  
- `#355 Roost`  
- `#456 Heal Order`

## `Badly Poison Target` {#badly-poison-target}

- `#092 Toxic`

## `Light Screen` {#light-screen}

- `#113 Light Screen`

  ### `Expert (Flag 2)` {#expert-(flag-2)-9}

| `User’s Current HP` | `Target Atk is greater than Target SpAtk` | `Score Change` |
| :---: | :---: | :---: |
| `1–49.999%` |  | `-2 (88.2353%) +0 (11.7647%)` |
| `50–89.999%` | `TRUE` | `-2 (88.2353%) +0 (11.7647%)` |
|  | `FALSE` | `+0 (25.0980%) +1 (74.9020%)` |
| `90%-100%` | `TRUE` | `-2 (10.3806%) -1 (77.8547%) +0 ( 1.3841%) +1 (10.3806%)` |
|  | `FALSE` | `+0 ( 2.9527%) +1 (30.9573%) +2 (66.0900%)` |

## `Rest` {#rest}

- `#156 Rest`

## `OHKO` {#ohko}

- `#012 Guillotine`  
- `#032 Horn Drill`  
- `#090 Fissure`  
- `#329 Sheer Cold`

  ### `No Effect (Flag 0)` {#no-effect-(flag-0)-7}

| `Move effectiveness is... 0×` | `User has... Mold Breaker` | `Guess target’s ability` | `Score Change` |
| :---: | :---: | :---: | :---: |
| `TRUE` |  |  | `-10` |
| `FALSE` | `TRUE` |  | `See next table...` |
|  | `FALSE` | `Sturdy` | `-10` |
|  |  | `Other` | `See next table...` |


| `User’s level < target’s level` | `Score Change` |
| :---: | :---: |
| `TRUE` | `-10` |
| `FALSE` | `+0` |

  ### `Expert (Flag 2)f` {#expert-(flag-2)f}

| `Score Change` |
| :---: |
| `+0 (75%) +1 (25%)` |

## `Two-turn (Standard)` {#two-turn-(standard)}

- `#013 Razor Wind`  
- `#130 Skull Bash`

  ### `Expert (Flag 2)` {#expert-(flag-2)-10}

| `Move Effectiveness` | `User has... Power Herb` | `Target has... Protect and/or Detect` | `User’s Current HP` | `Score Change` |
| :---: | :---: | :---: | :---: | :---: |
| `0×1/4×1/2×` |  |  |  | `-2` |
| `1×2×4×` | `TRUE` |  |  | `+2` |
|  | `FALSE` | `TRUE` |  | `-2` |
|  |  | `FALSE` | `1–38%` | `-1` |
|  |  |  | `38.001–100%` | `+0` |

## `Direct Damage (Half)` {#direct-damage-(half)}

- `#162 Super Fang`


| `Target’s current HP` | `Score Change` |
| :---: | :---: |
| `0-59.999%` | `-1` |
| `60-100%` | `+0` |

  ### 

## `Direct Damage (40 HP)` {#direct-damage-(40-hp)}

- `#082 Dragon Rage`

## `Trapping` {#trapping}

- `#020 Bind`  
- `#035 Wrap`  
- `#083 Fire Spin`  
- `#128 Clamp`  
- `#250 Whirlpool`  
- `#328 Sand Tomb`  
- `#463 Magma Storm`

  ### `Expert (Flag 2)` {#expert-(flag-2)-11}

| `Target has... Bad Poison, Curse, Perish Song, and/or Infatuation` | `Score Change` |
| :---: | :---: |
| `TRUE` | `+0 (50%) +1 (50%)` |
| `FALSE` | `+0` |

## `Increased Critical Hit Ratio` {#increased-critical-hit-ratio}

- `#002 Karate Chop`  
- `#075 Razor Shell`  
- `#152 Crabhammer`  
- `#163 Slash`  
- `#177 Aeroblast`  
- `#238 Cross Chop`  
- `#299 Blaze Kick`  
- `#314 Air Cutter`  
- `#342 Poison Tail`  
- `#348 Leaf Blade`  
- `#400 Night Slash`  
- `#421 Shadow Claw`  
- `#427 Psycho Cut`  
- `#440 Cross Poison`  
- `#444 Stone Edge`  
- `#454 Attack Order`  
- `#460 Spacial Rend`  
- `#529 Drill Run`

  ### `Expert (Flag 2)` {#expert-(flag-2)-12}

| `Move Effectiveness` | `Score Change` |
| :---: | :---: |
| `0×1/4×1/2×` | `+0` |
| `1×` | `+0 (75%) +1 (25%)` |
| `2×4×` | `+0 (50%) +1 (50%)` |

## `Semi-Invulnerable (Except Shadow Force)` {#semi-invulnerable-(except-shadow-force)}

- `#019 Fly`  
- `#091 Dig`  
- `#291 Dive`  
- `#340 Bounce`

  ### `Expert (Flag 2)` {#expert-(flag-2)-13}

| `User has... Power Herb` | `Target has... Protect and/or Detect` | `Move Effectiveness` | `User is faster than Target` | `User’s Current HP` | `User has... Custap Berry` | `Score Change` |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| `TRUE` |  |  |  |  |  | `+2` |
| `FALSE` | `TRUE` |  |  |  |  | `-1` |
|  | `FALSE` | `0×1/4×1/2×` |  |  |  | `+1` |
|  |  | `1× 2× 4×` | `FALSE` | `1–24%` | `TRUE` | `+0 (31.25%) +1 (68.75%)` |
|  |  |  |  |  | `FALSE` | `See next table...` |
|  |  |  |  | `24.001–100%` |  |  |
|  |  |  | `TRUE` |  |  |  |

| `Target has... Bad Poison, Curse, and/or Leech Seed` | `Weather` | `User’s Type` | `Score Change` |
| :---: | :---: | :---: | :---: |
| `TRUE` |  |  | `+0 (31.25%) +1 (68.75%)` |
| `FALSE` | `Sandstorm` | `Ground, Rock, or Steel` | `+0 (31.25%) +1 (68.75%)` |
|  |  | `Other` | `See next table...` |
|  | `Hail` | `Ice` | `+0 (31.25%) +1 (68.75%)` |
|  |  | `Other` | `See next table...` |
|  | `Sun, Rain, or None` |  | `See next table...` |

| `User is slower than Target` | `Target’s previous move was... Mind Reader or Lock-On` | `Score Change` |
| :---: | :---: | :---: |
| `TRUE` |  | `+0` |
| `FALSE` | `TRUE` | `+0` |
|  | `FALSE` | `+0 (31.25%) +1 (68.75%)` |

## `Focus Punch` {#focus-punch}

- `#264 Focus Punch`

  ### `No Effect (Flag 0)` {#no-effect-(flag-0)-8}

| `Move effectiveness is... 0×` | `Guess target’s ability` | `User’s ability is... Mold Breaker` | `Move Effectiveness` | `Score Change` |
| :---: | :---: | :---: | :---: | :---: |
| `TRUE` |  |  |  | `-10` |
| `FALSE` | `Wonder Guard` |  |  | `+0` |
|  | `Other` | `TRUE` |  | `+0` |
|  |  | `FALSE` | `1/4× 1/2× 1×` | `-10` |
|  |  |  | `2× 4×` | `+0` |

  ### `Evaluate (Flag 1)` {#evaluate-(flag-1)-1}

| `Move will KO target` | `Is strongest move` | `Move effectiveness is... 4×` |  | `Score Change` |
| :---: | :---: | :---: | :---: | :---: |
| `TRUE` |  |  |  | `+0 (66.4063%) +4 (33.5938%)` |
| `FALSE` | `TRUE` | `TRUE` |  | `-2 (25.0244%) +0 (61.2793%) +2 (13.6963%)` |
|  |  | `FALSE` |  | `-2 (80.0781%) +0 (19.9219%)` |
|  | `FALSE` |  |  | `-1` |

  ### 

# `Contributing`

# `Contributing`

`There are a lot of moves with a lot of specialized logic, so any assistance in indexing the flowcharts is greatly appreciated!`

`For access to editing this document, contact DaSquyd on Discord.`

# **`Important Notes`**

`This guide is purely for adding new flowcharts. It does not provide details on the process of analyzing the AI logic for any given move.`

# **`Getting Started`**

`First, ensure that the Mermaid Google Docs Add-on is installed:`

| `![][image18]` |
| :---: |

`If it’s not, select “Add-ons”, “Get Add-ons”, and search for “Mermaid - Diagramming and charting tool”.`

| `![][image19]` |
| :---: |

# **`Creating a Flowchart`**

`Head over to Mermaid Chart to get started with flowchart creation. The flowcharts should follow a standard format much like the following example:`

| `--- config:   theme: redux-dark   layout: dagre   look: neo --- flowchart TD     Start(["Start"])     TargetsAccuracyStatStage{"Target's         Accuracy         Stat Stage"}     UsersCurrentHP{"User's         Current         HP"}     UserIsSlowerThanTarget{"User is         slower than         target"}     MidA["-1"]     MidB["-2 (50%)         -2 (50%)"]     EndA["-3 (80.4688%, common)         +0 (19.5313%, common)"]     EndB["-1 (80.4688%, common)         +0 (19.5313%, common)"]     EndC["+0 (50%, common)         +1 (50%, common)"]     EndD["+0 (25%, common)         +1 (50%, common)         +2 (25%, common)"]     Start --> TargetsAccuracyStatStage     TargetsAccuracyStatStage -- -6 to 0 --> UsersCurrentHP     TargetsAccuracyStatStage -- +1 to +3 --> MidA --> UsersCurrentHP     TargetsAccuracyStatStage -- +4 to +6 --> MidB --> UsersCurrentHP     UsersCurrentHP -- ≤30% --> EndD     UsersCurrentHP -- ≥80% --> UserIsSlowerThanTarget     UsersCurrentHP -- \>50% and <80% --> EndB     UsersCurrentHP -- \>30% and ≤50% --> EndC     UserIsSlowerThanTarget -- FALSE --> EndA     UserIsSlowerThanTarget -- TRUE --> EndB` |
| :---- |

`On the site it should look something like this:`

| `![][image20]` |
| :---- |

`You can find Mermaid’s full documentation here.`

## `Best Practices`

- `Use the “redux-dark” theme with “dagre” layout and “neo” look.`  
- `Follow existing naming conventions.`  
- `Avoid crossing paths whenever possible.`  
- `Split text across multiple lines to avoid large nodes.`  
  - `For decisions, aim for the center line to be the largest to fit the diamond shape best.`  
- `Align numbers vertically for better readability (+0 instead of just 0)`

# **`Importing`**

`To import the flowchart to this document after you’ve designed it to your liking, first press the “Export” button in the top bar, on the right.`

| `![][image21]` |
| :---: |

`This should bring up a window like the following:`

| `![][image22]` |
| :---: |

`Next, set the “Background color” to transparent:`

| `![][image23]` |
| :---: |

`Then, copy the image by clicking the copy button in the top right corner of the preview:`

| `![][image24]` |
| :---: |

`In this document, pase the copied image at the intended location.`

| `![][image25]` |
| :---: |

`Head back to Mermaid and copy the code. Next, back in this document, go to “Extensions” and then “Mermaid - ...” and finally “New chart”.`

| `![][image26]` |
| :---: |

`This will open the graph editor. Paste the copied code into the section labeled “source code of your graph”.`

| `![][image27]` |
| :---: |

`All we’re actually using this for is to observe the size value in pixels provided by this tool. In the future, we’ll likely have a better way of handling this, but for now, take a look at the bottom of the window:`

| `![][image28]` |
| :---: |

`We need to remember the first value, 878 in this case. Hit the “Cancel” button in the bottom right or the exit button in the top right to close this window.`

`Select the image that you pasted in earlier by left-clicking. This should reveal an “Image options” button in the toolbar that should be clicked.`

| `![][image29]` |
| :---: |

`In the image options, open up the dropdown titled “Size & rotation”. Set the width to be 1/100 of the number from earlier. In this case, 878 becomes 8.78 inches.`

| `![][image30]` |
| :---: |

`We do this to maintain a consistent scale across all images. We also avoid using the Mermaid extension to generate the images because they simply don’t look as good as the ones generated from the webapp. As previously mentioned, we might change this process in the future to streamline it.`
