#include "Game.h"

// void Game::display()
// {
//     m_screen.gotoXY(0, 19);
//     m_screen.printStringClearLine(std::to_string(static_cast<int>(m_timer.elapsed()) / 100));
//     //m_screen.printStringClearLine(std::to_string(m_rowsLeft));
//     m_screen.refresh();
// }

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
 : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_well(width, height, SPECIAL), m_score(0)
{
    m_rowsLeft = 5 * m_level;
}

void Game::play()
{
    m_well.displayWell(m_screen, WELL_X, WELL_Y);

    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();

    for(;;)
    {
        m_timer.start();
        m_well.clearWell();
        m_rowsLeft = 5 * m_level;
        displayStatus();
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        discardPendingKeys();
        m_level++;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
    //if new piece, then refresh next piece
    if(m_well.displayNext(m_screen, NEXT_PIECE_X, NEXT_PIECE_Y))
    {
        m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
        m_screen.printStringClearLine("Next piece: ");
    }

    m_screen.gotoXY(SCORE_X, SCORE_Y);
    m_screen.printStringClearLine("Score:     ");
    m_screen.gotoXY(SCORE_X + 12 - digits(m_score), SCORE_Y);
    //m_screen.printStringClearLine(std::to_string(digits(m_score)));
    m_screen.printStringClearLine(std::to_string(m_score));

    
    //included option of turning off levels
    if(LEVELS)
    {
        m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
        m_screen.printStringClearLine("Rows Left: ");
        m_screen.gotoXY(ROWS_LEFT_X + 12 - digits(m_rowsLeft), ROWS_LEFT_Y);
        m_screen.printStringClearLine(std::to_string(m_rowsLeft));

        m_screen.gotoXY(LEVEL_X, LEVEL_Y);
        m_screen.printStringClearLine("Level:     ");
        m_screen.gotoXY(LEVEL_X + 12 - digits(m_level), LEVEL_Y);
        m_screen.printStringClearLine(std::to_string(m_level));
    }
    

}

bool Game::playOneLevel()
    //at each timer, go one move
    //drop a piece if go finishes
{
    bool already = false; //makes sure a shift down only occurs once when timer is good
    char key = 's';
    int max = 1000 - (100 * (m_level - 1)); //for timer
    int rows = 0;
    
    //drops the first piece
    m_well.drop();
    m_well.displayInsides(m_screen, WELL_X, WELL_Y);
    displayStatus();

    while(m_rowsLeft > 0 || !LEVELS)
        //game loop. levels can be turned off
    {
        key = 's';
        if((static_cast<int>(m_timer.elapsed()) % 
            std::max(max, 100) == 0 && already) || getCharIfAny(key))
        {
            //exiting
            if(key == 'q' || key == 'Q')
            {
                return false;
            }
            //resets timer after piece shifts down
            if(key == 's' || key == '2')
            {
                m_timer.start();
            }

            already = false;
            if(m_well.go(key) == -1)
                //if piece has come to rest
            {
                //calculate score and rows left
                rows += m_well.clearRows();
                m_rowsLeft -= rows;
                if(m_rowsLeft <= 0)
                {
                    m_rowsLeft = 0;
                }

                if(rows != 0)
                {
                    m_score += 100 * std::pow(2, rows - 1);
                }
                rows = 0;
                
                //generates new piece and soldifies
                if(!m_well.drop()) return false;

                //refreshes status
                displayStatus();
            }
            m_well.displayInsides(m_screen, WELL_X, WELL_Y);
        }

        //makes sure a shift down only occurs once
        if(!(static_cast<int>(m_timer.elapsed()) % std::max(max, 100) == 0))
        {
            already = true;
        }
    }

        

    return true;
}

int Game::digits(int num)
{
    int counter = 0;
    if(num > 9)
    {
        counter++;
    }

    while(num / 10 >= 10)
    {
        counter++;
        num /= 10;
    }

    return counter;
}




