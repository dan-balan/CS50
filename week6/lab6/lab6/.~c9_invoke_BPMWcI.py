# Simulate a sports tournament

import csv
import sys
import random
import copy

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # Read teams into memory from file
    filename = sys.argv[1]              # "2018m.csv"
    with open(filename, "r") as file:
        reader = csv.DictReader(file)
        #next(reader)
        for row in reader:
            row["rating"] = int(row["rating"])
            teams.append(row)

    for team in teams:
        for t, r in team.items():
            print(t + ": " + str(r))
        #print("\n")
    print(f"lungimea list {len(teams)}")

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
        for team in teams:
        for t, r in team.items():
            counts[t[team]] = 0
    simulate_tournament(teams)

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")

    for team in counts:
        print(f"{team} : {counts[team]}")

def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    worldCup = copy.copy(teams)

        game_round = simulate_round(worldCup)
        worldCup.clear()
        worldCup = copy.copy(game_round)

    return worldCup

if __name__ == "__main__":
    main()
