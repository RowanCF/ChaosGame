

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

Vector2f randomVertexPositionSquare(vector<RectangleShape> vertices);
RectangleShape Point(float x, float y);
Vector2f RandomVertexPosition(vector<RectangleShape> vertices);
Vector2f randomVertexPositionPentagon(vector<RectangleShape> vertices);
Vector2f randomVertexButNotSameAsLast(vector<RectangleShape> vertices, int lastVertexIndex);
vector<RectangleShape> drawSquare(RenderWindow& window);

void CenterTextRectOrigin(Text& text);

void square2(int sizeRatio) 
{
    
    srand(time(0));

    // Defines the rate of drawing in seconds. Decreasing this value will make the drawing process
    // slower a little bit. But you will see many points drawn in realtime.
    float drawingRate = 0.001;    // was 0.5
    float nextTimeToDraw = 0;
    double elapsedTime = 0;

    Clock clock;

    int screenRes_X = 1920;
    int screenRes_Y = 1080;

    // Setting up a point count display
    Text pointCount2;
    Font font;
    font.loadFromFile("Fonts/sf-atarian-system.regular.ttf");
    pointCount2.setFont(font);
    pointCount2.setString("point count: ");
    int startGameTextCharSize = 30 * sizeRatio;
    pointCount2.setCharacterSize(startGameTextCharSize);
    pointCount2.setPosition((screenRes_X / 2.0f) - 400, 450.0f * sizeRatio);
    CenterTextRectOrigin(pointCount2);

    Text pointCount;
    //Font font;
    font.loadFromFile("Fonts/sf-atarian-system.regular.ttf");
    pointCount.setFont(font);
    pointCount.setString("point count: ");
    //int startGameTextCharSize = 30 * sizeRatio;
    pointCount.setCharacterSize(startGameTextCharSize);
    pointCount.setPosition(screenRes_X / 2.0f, 450.0f * sizeRatio);
    CenterTextRectOrigin(pointCount);

    VideoMode videoModeObject(screenRes_X, screenRes_Y);
    RenderWindow window(videoModeObject, "Chaos Game", Style::Default);

    RectangleShape myShape;

    Vector2f size;      // my more wordy way of doing it
    size.x = 3;
    size.y = 3;

    //ShapeType shapeType = ShapeType::SQUARE;

    vector<RectangleShape> shapeVertices;
    vector<RectangleShape> pointsToDraw;

    RectangleShape starterPoint;
    RectangleShape midwayPoint;
    RectangleShape previousPoint;

    RectangleShape lastVertex;
    Vector2f lastVertexPos;
    int lastVertexIndex = 0;

    Vector2f randomVertex;

    bool firstRun = true;

    int counter = 0;    
    while (window.isOpen())
    { 
        window.display();

        // Closes the game window if the user pressed the Escape button.
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        Time deltaTime = clock.restart();
        Vector2i mousePosition;
        Event event;

        // Checks if the user pressed left mouse button.
        bool isLeftMouseButtonPressed;
        isLeftMouseButtonPressed = false;
        while (window.pollEvent(event))
        {
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    isLeftMouseButtonPressed = true;
                }
            }
        }
        // If user clicks, record where
        if (isLeftMouseButtonPressed == true)
        {
            mousePosition.x = event.mouseButton.x; 
            mousePosition.y = event.mouseButton.y;
        }

        // Draw the starting square and display it on the screen
        vector<RectangleShape> squareVertexList;
        squareVertexList = drawSquare(window);
        window.display();

        // If user has not yet clicked somewhere inside the square,
        // then "prepare" for a click, and then make a note of where it was when it happens.
        if (starterPoint.getPosition() == Vector2f(0, 0))   
        {
            if (isLeftMouseButtonPressed)     
            {
                mousePosition = Mouse::getPosition(window);
                starterPoint = Point(mousePosition.x, mousePosition.y);
                previousPoint = starterPoint;
            }
        }

        else
        {
            // If this is the first run, through automatic part of the program, make sure the "last vertex" is arbitrarily set to something.
            if (firstRun == true)  
            {
                lastVertexPos = squareVertexList[0].getPosition();
                lastVertex = squareVertexList[0];
                lastVertexIndex = 0;

                if (isLeftMouseButtonPressed)   // And if the user clicks, then set that to the first point.
                {
                    //cout << "Raisin2" << endl;
                    mousePosition = Mouse::getPosition(window);
                    starterPoint = Point(mousePosition.x, mousePosition.y);
                    previousPoint = starterPoint;
                }
                // This block will not happen again because the first run happens only once by definition
                firstRun = false;   
            }

            // If this is not the first run, choose a random vertex and then find the midway point between it, and the previous point. Afterwards, 
            // set this midway point to be the previous point once you have used it.
            else
            {
                randomVertex = randomVertexPositionSquare(squareVertexList); // While this is returning lastVertexPos....
                while (randomVertex == lastVertexPos)
                {
                    randomVertex = randomVertexPositionSquare(squareVertexList); // .....try again until it chooses something else
                }

                lastVertexPos = randomVertex;
                firstRun = false;

                double midwayPointX = (randomVertex.x + previousPoint.getPosition().x) / 2.0;
                double midwayPointY = (randomVertex.y + previousPoint.getPosition().y) / 2.0;
                midwayPoint = Point(midwayPointX, midwayPointY);
                previousPoint = midwayPoint;

                pointsToDraw.push_back(previousPoint);

                counter++;  // Not currently in use
            }
        }

        Color color;
        color.r = 40;
        color.b = 255;
        color.g = 0;

        //Color color2;
        //color2.r = 200;      
        
       
        // Print out a count of the number of points drawn
        elapsedTime += 1 * deltaTime.asSeconds();
        if (elapsedTime >= nextTimeToDraw)
        {
            nextTimeToDraw = drawingRate + elapsedTime;
            string pointCountStr = to_string(pointsToDraw.size());
            pointCount.setString(pointCountStr);
            window.clear(); //                             
        }
        window.draw(pointCount);    // ** Stuttering issue occurs when placed in above loop **
        
        // Color and draw the points in the vector
        for (auto& point : pointsToDraw)
        {
            point.setFillColor(color);
            window.draw(point);                   
        }

        // Print user instructions
        Text instructions = pointCount;
        instructions.setCharacterSize(22);
        instructions.setString("For the square, the vertices have been chosen automatically so that it's easy to get a perfect square. Just click somewhere inside.");
        instructions.setPosition(425, 150);
        window.draw(instructions);

        window.draw(pointCount2);
        window.display();



    } //end while loop

 
}