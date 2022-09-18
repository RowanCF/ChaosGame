#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

// Instantiate rectangle shape to be drawn as a point.
RectangleShape Point(float x, float y)
{
    RectangleShape rectangle;

    rectangle.setSize(Vector2f(1, 1));  // Was 3 before
    rectangle.setPosition(x, y);

    return rectangle;
}

// Pick random vertex.
Vector2f RandomVertexPosition(vector<RectangleShape> vertices)
{
    int randomIndex = 0 + rand() % 3;

    return vertices[randomIndex].getPosition();
}

// Pick random vertex for a square.
Vector2f randomVertexPositionSquare(vector<RectangleShape> vertices)
{
    int randomIndex = 0 + rand() % 4;

    return vertices[randomIndex].getPosition();
}

// Pick random vertex for a hexagon.
Vector2f randomVertexPositionHexagon(vector<RectangleShape> vertices)
{
    int randomIndex = 0 + rand() % 6;

    return vertices[randomIndex].getPosition();
}

// Pick random vertex, but it cannot be the same vertex as last run
Vector2f randomVertexButNotSameAsLast(vector<RectangleShape> vertices, int lastVertexIndex)
{

    int randomIndex = 0 + rand() % 4;
    while (randomIndex != lastVertexIndex)
    {
        randomIndex = 0 + rand() % 4;
    }

    return vertices[randomIndex].getPosition();

}


// Draw a starting square
vector<RectangleShape> drawSquare(RenderWindow& window)
{
    Vector2f size;
    size.x = 3;
    size.y = 3;

    Vector2f topLeftPos;
    Vector2f topRightPos;
    Vector2f bottomLeftPos;
    Vector2f bottomRightPos;

    topLeftPos.x = 600;
    topLeftPos.y = 200;
    topRightPos.x = 1200;
    topRightPos.y = 200;

    bottomLeftPos.x = 600;
    bottomLeftPos.y = 800;
    bottomRightPos.y = 800;
    bottomRightPos.x = 1200;

    RectangleShape topLeft;
    RectangleShape topRight;
    RectangleShape bottomLeft;
    RectangleShape bottomRight;

    topRight.setSize(size);
    topLeft.setSize(size);
    bottomLeft.setSize(size);
    bottomRight.setSize(size);

    topLeft.setPosition(topLeftPos.x, topLeftPos.y);
    topRight.setPosition(topRightPos.x, topRightPos.y);
    bottomRight.setPosition(bottomRightPos.x, bottomRightPos.y);
    bottomLeft.setPosition(bottomLeftPos.x, bottomRightPos.y);

    vector<RectangleShape> localVector{ topLeft, topRight, bottomLeft, bottomRight };

    window.draw(topLeft);
    window.draw(topRight);
    window.draw(bottomLeft);
    window.draw(bottomRight);
    window.display();

    for (auto& point : localVector)
    {
        window.draw(point);
        
    }
    window.display();

    return localVector;

}

void CenterTextRectOrigin(Text& text);

enum ShapeType
{
    TRIANGLE,
    hexagon,
    SQUARE
};

// -----------------------------------------
// -----------------------------------------

void hexagon2(int sizeRatio) 
{  
    srand(time(0));

    // Defines the rate of drawing in seconds. Decreasing this value will make the drawing process
    // slower a little bit. But you will see many points drawn in realtime.
    float drawingRate = 0.06;    
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

    Vector2f size;
    size.x = 3;
    size.y = 3;

    vector<RectangleShape> hexagonVertexList;
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
       // Closes the game window if the user presses the Escape Button
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        Time deltaTime = clock.restart();
        Vector2i mousePosition;
        Event event;

        // Checks if the user pressed left mouse button
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

         // If user has not yet selected all vertices, then keep getting the vertices       
        if (hexagonVertexList.size() < 6)
        {
            if (isLeftMouseButtonPressed == true)
            {
                mousePosition = Mouse::getPosition(window);
                hexagonVertexList.push_back(Point(mousePosition.x, mousePosition.y));
            }
        }

        else
        {
            // If user has selected the vertices
            // but not yet selected the starter point, that is the first point after selecting
            //  the vertices,
            // then collect it from them, and also set previousPoint equal to the same as 
            // whatever you get from the user
            if (starterPoint.getPosition() == Vector2f(0, 0))
            {
                if (isLeftMouseButtonPressed)
                {
                    mousePosition = Mouse::getPosition(window);
                    starterPoint = Point(mousePosition.x, mousePosition.y);
                    previousPoint = starterPoint;
                    pointsToDraw.push_back(previousPoint);
                }
            }

            // START PRINTING POINTS ACCORDING TO ALGORITHM
            // If the user has selected the vertices and the starter point
            // go agead and start main algorithm
            else
            {    // If this is first run of main algorithm, make sure the "last vertex" is 
                // arbitrarily set to something
                if (firstRun == true)
                {
                    lastVertexPos = hexagonVertexList[0].getPosition();
                    lastVertex = hexagonVertexList[0];
                    lastVertexIndex = 0;

                    // And then if the user clicks, set that to the first point
                    if (isLeftMouseButtonPressed)
                    {
                        mousePosition = Mouse::getPosition(window);
                        starterPoint = Point(mousePosition.x, mousePosition.y);
                        previousPoint = starterPoint;
                    }

                    //Now that the first run is over, make sure this part doesn't happen again
                    firstRun = false;
                }

                // If this is not the first run, choose a random 
                // vertex and then find the 
                // midway point between it, 
                // and the previous point. Afterwards, 
                // set this midway point to be the previous point 
                // once you have added it to the vector of points to draw.
                else
                {
                    // This block prevents the same vertex being chosen twice in a row.
                    // Turns it on for an interesting alternative fractal.
                    /*
                    while (randomVertex == lastVertexPos)
                    {
                        // Trying again...
                        randomVertex = randomVertexPositionHexagon(hexagonVertexList);
                    }
                    */

                    // Deactivate this line if you turn on the block just above
                    randomVertex = randomVertexPositionHexagon(hexagonVertexList);    

                    lastVertexPos = randomVertex;
                    firstRun = false;   

                    //Turn these on instead for a snowflake-like fractal
                    /*
                    double midwayPointX = (randomVertex.x + previousPoint.getPosition().x) / 2.0;   
                    double midwayPointY = (randomVertex.y + previousPoint.getPosition().y) / 2.0;
                    */

                    double midwayPointX = ((randomVertex.x + previousPoint.getPosition().x) / 3.0) + 250;
                    double midwayPointY = ((randomVertex.y + previousPoint.getPosition().y) / 3.0) + 170;

                    midwayPoint = Point(midwayPointX, midwayPointY);
                    previousPoint = midwayPoint;

                    // We have the midway point, so adding it to the vector now
                    pointsToDraw.push_back(previousPoint);
                   // cout << "main part2" << endl;

                    //counter++;  
                }
            }
        }

        
        // Printing out the user-selected vertices   
         for (int index = 0; index < hexagonVertexList.size(); index++)
         {          
              //window.draw(hexagonVertexList[index]);  
              window.draw(hexagonVertexList.at(index));
         }
       
        /*
        // Does same as above loop
        for (RectangleShape point : hexagonVertexList)
        {
            window.draw(point);
        }
        */

         // Printing the algorithm-generated points
        elapsedTime += 1 * deltaTime.asSeconds();
        if (elapsedTime >= nextTimeToDraw)
        {
            nextTimeToDraw = drawingRate + elapsedTime;

            for (auto& point : pointsToDraw)
            {
                //point.setFillColor(color);
                window.draw(point);               
            }
        }

        // Print user instructions
        Text instructions = pointCount;
        instructions.setCharacterSize(22);
        instructions.setString("Click to designate the six vertices of a hexagon, then click somewhere inside it.");
        instructions.setPosition(425, 150);
        window.draw(instructions);
      
        window.display();

        counter++;  // Not currently in use

    }   // end main while loop
}