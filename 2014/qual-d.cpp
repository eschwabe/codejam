// Problem C. Deceitful War
// https://code.google.com/codejam/contest/2974486/dashboard#s=p3

#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

// read a line from stdin
std::stringstream ReadLine()
{
    std::string tmp;
    std::getline(std::cin, tmp);
    return std::stringstream(tmp);
}

// stores players current blocks and performs actions on them
class Player
{
public:

    Player (std::list<double> blocks)
    {
        blocks.sort();
        blocks_original_ = blocks;
        blocks_current_ = blocks;
    }
    virtual ~Player () {}

    // play a block with no information about other player
    double PlayBlock()
    {
        double value = blocks_current_.front();
        blocks_current_.pop_front();
        return value;
    }

    // play a block knowing the other players block
    double PlayBlock(double block_to_beat)
    {
        // find a block slightly larger
        auto iter = blocks_current_.begin();
        while(iter != blocks_current_.end())
        {
            if(*iter > block_to_beat) {
                double block_to_play = *iter;
                blocks_current_.erase(iter);
                return block_to_play;
            }
            iter++;
        }

        // else, play smallest and lose round
        double block_to_play = blocks_current_.front();
        blocks_current_.erase(blocks_current_.begin());
        return block_to_play;
    }

    // play a block knowing the other players current blocks and provide false block value
    // unless guarenteed to win
    double PlayDeceitfulBlock(Player& other)
    {
        // check if remaining plays will win
        bool win_condition = true;
        auto p1block = blocks_current_.begin();
        auto p2block = other.blocks_current_.begin();

        while(p1block != blocks_current_.end() && p2block != other.blocks_current_.end()) {
            if(*p1block < *p2block) {
                win_condition = false;
                break;
            }
            p1block++;
            p2block++;
        }

        // if win condition, play first block with value greater than other players largest
        // forces other player to play their smallest block
        if(win_condition)
        {
            blocks_current_.pop_front();
            return other.blocks_current_.back() + 1E-9;
        }
        // else, play smallest block with a false value to force other player to play largest
        else
        {
            blocks_current_.pop_front();
            return other.blocks_current_.back() - 1E-9;
        }
    }

    // reset blocks to original state (new game)
    void Reset()
    {
        blocks_current_ = blocks_original_;
    }

    void PrintBlocks()
    {
        std::copy(blocks_current_.begin(), blocks_current_.end(), std::ostream_iterator<double>(std::cout, " "));
        std::cout << std::endl;
    }

    int GetCurrentBlockCount()
    {
        return blocks_current_.size();
    }

private:
    std::list<double> blocks_current_;
    std::list<double> blocks_original_;

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
};

// play game of war as player 1
int War(Player& p1, Player& p2)
{
    int p1_wins = 0;

    while(p1.GetCurrentBlockCount() != 0) {
        double p1block = p1.PlayBlock();
        double p2block = p2.PlayBlock(p1block);

        //std::cout << "P1: " << p1block << "  P2: " << p2block << std::endl;

        if(p1block > p2block) {
            p1_wins++;
        }
    }

    return p1_wins;
}

// player game of deceiful war as player 1
int DeceitfulWar(Player& p1, Player& p2)
{
    int p1_wins = 0;

    while(p1.GetCurrentBlockCount() != 0) {
        double p1block = p1.PlayDeceitfulBlock(p2);
        double p2block = p2.PlayBlock(p1block);

        //std::cout << "P1: " << p1block << "  P2: " << p2block << std::endl;

        if(p1block > p2block) {
            p1_wins++;
        }
    }

    return p1_wins;
}

int main()
{
    int num_tests = 0;
    std::stringstream line = ReadLine();
    line >> num_tests;

    for(int tcase = 1; tcase <= num_tests; tcase++ ) {

        // read input
        int num_blocks = 0;
        line = ReadLine();
        line >> num_blocks;

        std::stringstream p1_block_stream = ReadLine();
        std::stringstream p2_block_stream = ReadLine();
        auto p1_blocks = std::list<double>();
        auto p2_blocks = std::list<double>();

        for(int block = 0; block < num_blocks; block++) {
            double weight1 = 0.0;
            double weight2 = 0.0;

            p1_block_stream >> weight1;
            p2_block_stream >> weight2;

            p1_blocks.push_back(weight1);
            p2_blocks.push_back(weight2);
        }

        // build players
        Player p1(p1_blocks);
        Player p2(p2_blocks);

        //p1.PrintBlocks();
        //p2.PrintBlocks();

        // compute war wins
        int p1_war_wins = War(p1, p2);

        // compute deceitful war wins
        p1.Reset();
        p2.Reset();
        int p1_deceitful_war_wins = DeceitfulWar(p1, p2);

        // show results
        std::cout << "Case #" << tcase << ": " << p1_deceitful_war_wins << " " << p1_war_wins << std::endl;

    }

    return 0;
}
