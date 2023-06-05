#!/bin/bash

# Function to simulate a match between two teams
simulate_match() {
    team1=$1
    team2=$2
    score1=$((RANDOM % 6))  # Random score for team 1 (0-5)
    score2=$((RANDOM % 6))  # Random score for team 2 (0-5)
    echo "$team1 $score1 - $score2 $team2"
}

# Read the number of participating teams
echo -n "Enter the number of participating teams: "
read num_teams

# Validate the input
if [[ $num_teams -lt 2 ]]; then
    echo "Invalid number of teams. Exiting."
    exit 1
fi

teams=()

# Read the team names
for ((i=1; i<=num_teams; i++)); do
    echo -n "Enter the name of team $i: "
    read team
    teams+=("$team")
done

# Simulate the tournament matches
num_matches=$((num_teams - 1))
match_count=1

echo "----- TOURNAMENT SIMULATION -----"

while [[ $num_matches -gt 0 ]]; do
    echo ""
    echo "Match $match_count:"

    # Select two random teams
    team1_index=$((RANDOM % num_teams))
    team1=${teams[$team1_index]}
    echo -n "$team1 vs "

    # Remove team1 from the array
    teams=("${teams[@]:0:$team1_index}" "${teams[@]:$((team1_index + 1))}")

    team2_index=$((RANDOM % (num_teams - 1)))
    team2=${teams[$team2_index]}
    echo "$team2"

    # Simulate the match
    simulate_match "$team1" "$team2"

    match_count=$((match_count + 1))
    num_matches=$((num_matches - 1))
done

# Display tournament results
echo ""
echo "----- TOURNAMENT RESULTS -----"

for team in "${teams[@]}"; do
    echo "$team"
done

