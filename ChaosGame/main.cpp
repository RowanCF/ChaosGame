#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

// Center the origin of the text transform.
void CenterTextRectOrigin(Text& text)
{
    FloatRect rect = text.getLocalBounds();
    text.setOrigin(rect.left + rect.width / 2.0f,
        rect.top + rect.height / 2.0f);
}

// Currently unused
void displaySelectShapeTypeScreen(RenderWindow & window, Font & font )
{
    bool go = true;
    while (window.isOpen())
    {
        window.clear();
        window.display();
        cout << "yay";
    }
}

void hexagon2(int sizeRatio);
void square2(int sizeRatio);
void triangle2(int sizeRatio);


int main()
{
    Event event;

    Vector2i mousePosition;

    int screenRes_X = 1920;
    int screenRes_Y = 1080;

    // Change this value if you want to change the window resolution, to adjust all text sizes.
    // For example, for large resolution like 1920px1080p, change this ratio to 2. But for smaller ones
    // like 800px600p or 1024px768p, change the ratio to 1 to appear smaller.
    int sizeRatio = 2;

    RenderWindow window(VideoMode(screenRes_X, screenRes_Y), "Chaos Game", Style::Default);

    Cursor cursor;
    if (cursor.loadFromSystem(Cursor::Arrow))
    {
        window.setMouseCursor(cursor);
    }

    // Change this value whenever you want to make text transition more visible.
    float charSizeIncreaseRatio = 1.2;

    int gameTitleTextCharSize = 100 * sizeRatio;
    int startGameTextCharSize = 30 * sizeRatio;

    Font font;
    font.loadFromFile("Fonts/sf-atarian-system.regular.ttf");

    Text gameTitleText;
    Text startGameButtonText;

    gameTitleText.setFont(font);
    startGameButtonText.setFont(font);

    gameTitleText.setString("Chaos Game");
    startGameButtonText.setString(">> Start New Game <<");

    gameTitleText.setCharacterSize(gameTitleTextCharSize);
    startGameButtonText.setCharacterSize(startGameTextCharSize);

    gameTitleText.setPosition(screenRes_X / 2.0f, 100.0f * sizeRatio);
    startGameButtonText.setPosition(screenRes_X / 2.0f, 250.0f * sizeRatio);

    CenterTextRectOrigin(gameTitleText);
    CenterTextRectOrigin(startGameButtonText);

    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Get the mouse position.
        Vector2i position = Mouse::getPosition(window);

        // Detects if the mouse is hovering over it.
        if (startGameButtonText.getGlobalBounds().contains((Vector2f)position))
        {
            if (startGameButtonText.getCharacterSize() == startGameTextCharSize)
            {
                startGameButtonText.setCharacterSize(startGameTextCharSize * charSizeIncreaseRatio);
                CenterTextRectOrigin(startGameButtonText);
            }
        }
        else
        {
            if (startGameButtonText.getCharacterSize() != startGameTextCharSize)
            {
                startGameButtonText.setCharacterSize(startGameTextCharSize);
                CenterTextRectOrigin(startGameButtonText);
            }
        }

        // Checking if left mouse button is pressed
        bool isLeftMouseButtonPressed;
        isLeftMouseButtonPressed = false;
        while (window.pollEvent(event))
        {
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    isLeftMouseButtonPressed = true;
                    mousePosition = Mouse::getPosition(window);
                }
            }
        }

        // If user clicks on "start game"...
        if (startGameButtonText.getGlobalBounds().contains((Vector2f)mousePosition))
        {
            
            // ...then trigger this lower while loop to handle the shape-selection screen
            bool backSelected = false;
            while (backSelected == false)
            {
                window.clear();

                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    window.close();
                }

                Color purple;
                purple.r = 80;
                purple.b = 200;

                Text prompt;
                Text triangle;
                Text square;
                Text hexagon;
                Text backButton;

                prompt.setFont(font);
                triangle.setFont(font);
                square.setFont(font);
                hexagon.setFont(font);
                backButton.setFont(font);

                prompt.setString("Select a shape:");
                triangle.setString("Triangle");
                square.setString("Square");
                hexagon.setString("Hexagon");
                backButton.setString("Back");

                prompt.setCharacterSize(gameTitleTextCharSize);
                triangle.setCharacterSize(startGameTextCharSize);
                square.setCharacterSize(startGameTextCharSize);
                hexagon.setCharacterSize(startGameTextCharSize);
                backButton.setCharacterSize(startGameTextCharSize);

                prompt.setPosition(screenRes_X / 2.0f, 150.0f * sizeRatio);
                triangle.setPosition(screenRes_X / 2.0f, 300.0f * sizeRatio);
                square.setPosition(screenRes_X / 2.0f, 350.0f * sizeRatio);
                hexagon.setPosition(screenRes_X / 2.0f, 400.0f * sizeRatio);
                backButton.setPosition(screenRes_X / 2.0f, 450.0f * sizeRatio);

                CenterTextRectOrigin(prompt);
                CenterTextRectOrigin(triangle);
                CenterTextRectOrigin(square);
                CenterTextRectOrigin(hexagon);
                CenterTextRectOrigin(backButton);

                window.draw(prompt);
                window.draw(triangle);
                window.draw(square);
                window.draw(hexagon);
                window.draw(backButton);

                vector<Text> textObjectList { /*prompt,*/ triangle, square, hexagon, backButton};

                


                // Get the mouse position.
                Vector2i position = Mouse::getPosition(window);

                // Detects if the mouse is hovering over it and changes color etc. accordingly.
                for (auto& textObject : textObjectList)
                {
                    if (textObject.getGlobalBounds().contains((Vector2f)position))
                    {
                        if (textObject.getCharacterSize() == startGameTextCharSize)
                        {
                            textObject.setCharacterSize(startGameTextCharSize * charSizeIncreaseRatio);

                            //triangle.setColor(purple);
                            textObject.setFillColor(purple);

                            CenterTextRectOrigin(textObject);
                        }
                    }
                    else
                    {
                        if (textObject.getCharacterSize() != startGameTextCharSize)
                        {
                            textObject.setCharacterSize(startGameTextCharSize);
                            CenterTextRectOrigin(textObject);
                        }
                    }
                }

                // Detects if mouse button is clicked
                isLeftMouseButtonPressed = false;
                while (window.pollEvent(event))
                {
                    if (event.type == Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == Mouse::Left)
                        {
                            isLeftMouseButtonPressed = true;
                            mousePosition = Mouse::getPosition(window);
                        }
                    }
                }

                
                // Starts up the triangle shape game when it is clicked on by the user
                if (textObjectList[0].getGlobalBounds().contains((Vector2f)mousePosition))
                {
                    //cout << "click" << endl;
                    triangle2(sizeRatio);
                }

                // Starts up the square shape game when it is clicked on by the user
                else if (textObjectList[1].getGlobalBounds().contains((Vector2f)mousePosition))
                {     
                    square2(sizeRatio);
                }

                // Starts up the hexagon shape game when it is clicked on by the user
                else if (textObjectList[2].getGlobalBounds().contains((Vector2f)mousePosition))
                {
                    hexagon2(sizeRatio);                   
                }

                // Goes back to the main menu if user clicks on back
                else if (textObjectList[3].getGlobalBounds().contains((Vector2f)mousePosition))
                {
                    backSelected = true;                   
                }
                
                window.clear();

                // Draws the buttons to the screen
                for (auto& textObject : textObjectList)
                {
                    window.draw(textObject);
                }

                
                window.draw(prompt);
                /*
                window.draw(triangle);
                window.draw(square);
                window.draw(hexagon);
                window.draw(backButton);
                */
                window.display();
            }
        }
        window.clear();
        window.draw(startGameButtonText);
        window.draw(gameTitleText);

        window.display();
    }


    return 0;
}