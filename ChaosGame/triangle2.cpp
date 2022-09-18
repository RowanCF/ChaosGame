
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

enum ShapeType
{
    TRIANGLE,
    PENTAGON,
    SQUARE
};



void triangle2(int sizeRatio)
{
    srand(time(0));

    Clock clock;

    // Defines the rate of drawing in seconds. Decreasing this value will make the drawing process
    // slower a little bit. But you will see many points drawn in realtime.
    float drawingRate = 0.5;
    float nextTimeToDraw = 0;
    double elapsedTime = 0;

    // Keeps track of total number of drawn points.
    int pointsCount = 0;

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
    pointCount2.setPosition( (screenRes_X / 2.0f) - 400, 450.0f * sizeRatio);
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
    // ------------------------------
    

    RenderWindow window(VideoMode(screenRes_X, screenRes_Y), "Chaos Game", Style::Default);     //How are you passing the first parameter like that

    // Let's assume that the user selected this shape.
    // We'll probably need to write a function to let the user select the prefered shape type.
    ShapeType shapeType = ShapeType::TRIANGLE;

    vector<RectangleShape> shapeVertices;
    vector<RectangleShape> pointsToDraw;

    RectangleShape starterPoint;
    RectangleShape midwayPoint;
    RectangleShape previousPoint;

    bool isLeftMouseButtonPressed = false;

    while (window.isOpen())
    {
        
        // Closes the game window if the user pressed the Escape button.
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        Time deltaTime = clock.restart();

        Vector2i mousePosition;

        Event event;

        // Checks if ther user pressed left mouse button.
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

        /************* The main algorithm to draw Sirpenski triangle. *************/
        if (shapeType == ShapeType::TRIANGLE)
        {
            // If user has not yet selected three vertices
            if (shapeVertices.size() < 3)
            {
                if (isLeftMouseButtonPressed)
                {
                    mousePosition = Mouse::getPosition(window);
                    shapeVertices.push_back(Point(mousePosition.x, mousePosition.y));
                }
            }
            else
            {
                // If user has not yet selected the starter point, that is the first point after selecting the vertices
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
                    // Start printing points according to the algorithm
                    Vector2f randomVertex = RandomVertexPosition(shapeVertices);

                    // Ask question about this syntax
                    Vector2f midwayPointPosition = Vector2f((randomVertex.x + previousPoint.getPosition().x) / 2.0, (randomVertex.y + previousPoint.getPosition().y) / 2.0);

                    midwayPoint = Point(midwayPointPosition.x, midwayPointPosition.y);

                    previousPoint = midwayPoint;

                    pointsToDraw.push_back(previousPoint);
                }
            }
        }

          // Print user instructions
        Text instructions = pointCount;
        instructions.setCharacterSize(22);
        instructions.setString("Click to set up the points of a triangle. Then click inside the triangle.");
        instructions.setPosition(450, 150);
        //window.draw(instructions);
        //window.display();

        if (starterPoint.getPosition() == Vector2f(0, 0))
        {
            window.clear();
            window.draw(instructions);
            for (RectangleShape vertex : shapeVertices)
            {
                
                window.draw(vertex);
            }

            window.display();
        }

      

        // Draw the generated points inside the shape to form the fractal.
        // Drawing a couple of thousands of points every specific amount of time will make the
        // drawing process more optimized.
        elapsedTime += 1 * deltaTime.asSeconds();
        if (elapsedTime >= nextTimeToDraw)
        {
            nextTimeToDraw = drawingRate + elapsedTime;

            window.clear();
            

            for (RectangleShape vertex : shapeVertices)
            {
                window.draw(vertex);
            }

            string pointCountStr = to_string(pointsCount);
            pointCount.setString(pointCountStr);

            for (int i = 0; i < (int)pointsToDraw.size(); i++)
            {
                window.draw(pointsToDraw[i]);
                window.draw(pointCount2);
                window.draw(pointCount);
                pointsCount++;
            }

            window.display();

            cout << "Number of points drawn: " << /*pointsCount*/ pointCountStr << endl;
        }
    } // end while loop

    //return 0;
}






