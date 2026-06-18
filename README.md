# LUDO

> IMPORTANT NOTICE: This README has been reviewed with a level of care that exceeds the care given to the actual source code by a factor of approximately 47.3. If you find a typo in the code, ignore it. If you find a typo here, submit a formal apology.

## 0. Abstract

ludo is a command line instrument for introducing calibrated uncertainty into deterministic computing environments. It does not solve problems. It decides whether problems deserve to be solved right now.

Version: 1.0.0
Author: xfredxcore
License: GPL v3
Last README Audit: 2026-06-19 09:14:33 UTC
Audit Duration: 3 hours 17 minutes
Auditors Present: 1 human, 1 very judgmental cat

## 1. Philosophy

ludo is built on three axioms

1. Not every command should run
2. Chance is a feature, not a bug
3. Im like documentations.

## 2. Installation

Do not rush installation. Installation is a ritual.

Step 1. Verify you have a POSIX compliant shell
Step 2. Verify gcc is at least here
Step 3. Create directory ~/.local/bin if wtf why do you haven’t it??
Step 4. Place ludo.c in a clean directory Step 5. Compile with exact flags

gcc ludo.c -o ~/.local/bin/ludo

Step 6. Run ludo -v
Step 7. Observe output. Meditate for 11 seconds
Step 8. Run ludo -c
Step 9. Accept the default chance of 50 percent
Step 10. Proceed to usage

Deviation from these steps voids the implied warranty of fun.

## 4. Command Reference

### 4.1 Flags

-v
Show version. Output includes bold ANSI escape sequence, version string, license identifier, author name. Exit code 0.

-c
Show current chance. Output format is exactly: Current chance: NN% 
Exit code 0.

-h
Show help. Help text is 217 characters long including newlines. Exit code 0.

### 4.2 Built in Commands

roll
Performs a single trial without executing external code. Prints Rolled X (chance Y%) -> success or fail. Returns 0 on success, 1 on fail.

set N
Sets chance to N where N is integer. Values below 0 are clamped to 0. Values above 100 are clamped to 100. Writes to ~/.ludo_chance atomically. Prints Chance set to N%

### 4.3 External Command Mode

Any token that is not -v, -c, -h, roll, or set is treated as external command. All following arguments are passed verbatim to execvp. 

Funny Example: ludo sudo rm -rf / —no-preserve-root

