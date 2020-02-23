/* *****************************************************************************
 *  Name:mike meng
 *  Date:2020.2.22
 *  Description:created by mike meng
 **************************************************************************** */

import edu.princeton.cs.algs4.StdOut;

public class BaseballElimination {
    public BaseballElimination(
            String filename) // create a baseball division from given filename in format specified
    {

    }

    public int numberOfTeams() // number of teams
    {

    }

    public Iterable<String> teams() // all teams
    {

    }

    public int wins(String team) // number of wins for given team
    {

    }

    public int losses(String team) // number of losses for given team
    {

    }

    public int remaining(String team) // number of remaining games for given team
    {

    }

    public int against(String team1,
                       String team2) // number of remaining games between team1 and team2
    {

    }

    public boolean isEliminated(String team) // is given team eliminated?
    {

    }

    public Iterable<String> certificateOfElimination(
            String team) // subset R of teams that eliminates given team; null if not eliminat
    {

    }

    public static void main(String[] args) {
        BaseballElimination division = new BaseballElimination(args[0]);
        for (String team : division.teams()) {
            if (division.isEliminated(team)) {
                StdOut.print(team + " is eliminated by the subset R = { ");
                for (String t : division.certificateOfElimination(team)) {
                    StdOut.print(t + " ");
                }
                StdOut.println("}");
            }
            else {
                StdOut.println(team + " is not eliminated");
            }
        }
    }
}
