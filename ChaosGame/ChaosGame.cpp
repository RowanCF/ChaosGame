

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

// Pick random vertex for a pentagon.
Vector2f randomVertexPositionPentagon(vector<RectangleShape> vertices)
{
    int randomIndex = 0 + rand() % 5;

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
vector<RectangleShape> drawSquare(RenderWindow & window)
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
    topRightPos.x = 1400;
    topRightPos.y = 200;

    bottomLeftPos.x = 600;
    bottomLeftPos.y = 800;
    bottomRightPos.y = 800;
    bottomRightPos.x = 1400;
    
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

    vector<RectangleShape> localVector {topLeft, topRight, bottomLeft, bottomRight};

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

enum ShapeType
{
    TRIANGLE,
    PENTAGON,
    SQUARE
};

// -----------------------------------------
// -----------------------------------------

int main5()
{
    srand(time(0));

    // Defines the rate of drawing in seconds. Decreasing this value will make the drawing process
    // slower a little bit. But you will see many points drawn in realtime.
    float drawingRate = 0.1;    // was 0.5
    float nextTimeToDraw = 0;
    double elapsedTime = 0;

    Clock clock;

    int screenRes_X = 1920;
    int screenRes_Y = 1080;

    VideoMode videoModeObject(screenRes_X, screenRes_Y);
    RenderWindow window(videoModeObject, "Chaos Game", Style::Default);

    RectangleShape myShape;

    Vector2f size;
    size.x = 3;
    size.y = 3;

    ShapeType shapeType = ShapeType::PENTAGON;  // This will need to be dealt with

    vector<RectangleShape> pentagonVertexList;
    vector<RectangleShape> shapeVertices; // Redundant with pentagonVertexList
    vector<RectangleShape> pointsToDraw;

    RectangleShape starterPoint;
    RectangleShape midwayPoint;
    RectangleShape previousPoint;

    RectangleShape lastVertex;
    Vector2f lastVertexPos;
    int lastVertexIndex = 0;

    Vector2f randomVertex;

    bool firstRun = true;

    int counter = 0;    // NOT CURRENTLY IN USE
    
    while (window.isOpen())
    {
        //window.display();

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
            //cout << "Cran1" << endl;
            if (event.type == Event::MouseButtonPressed)
            {
                //cout << "Cran2" << endl;
                if (event.mouseButton.button == Mouse::Left)
                {
                    //cout << "Cran3" << endl;
                    isLeftMouseButtonPressed = true;
                }
            }

        }

        //if (isLeftMouseButtonPressed == true)
        //{
        //   mousePosition.x = event.mouseButton.x;
        //    mousePosition.y = event.mouseButton.y;
        //}

      



        //if (shapeType == ShapeType::PENTAGON)
        //{ 
        
          // If user has not yet selected all vertices, then keep getting the vertices
        if (pentagonVertexList.size() < 5)
        {
            //cout << "Apple";
            if (isLeftMouseButtonPressed == true)
            {
                //cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl << endl;
                mousePosition = Mouse::getPosition(window);
                pentagonVertexList.push_back(Point(mousePosition.x, mousePosition.y));

                //EXPERIMENT
                //window.draw(Point(mousePosition.x, mousePosition.y));

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
                    lastVertexPos = pentagonVertexList[0].getPosition();
                    lastVertex = pentagonVertexList[0];
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
                    // STILL NEED TO WRITE THIS FUNCTION !!!!!!
                    // !!!####```|||[[[{{~#[{~#[~|{[`[||[\[|#\#[|\[|#
                    //-|[{||[{|#{|#{|#{|#{|{#|#{|#{|#{|#{|#{|#{|{#|#{-
                    randomVertex = randomVertexPositionPentagon(pentagonVertexList); // If this returns lastVertesPos, then the 
                                                                                    // while loop just below will be triggered
                                                                                    // until we get something other than lastVertexPos.
                    while (randomVertex == lastVertexPos)
                    {
                        // Trying again...
                        randomVertex = randomVertexPositionPentagon(pentagonVertexList);
                    }

                    lastVertexPos = randomVertex;
                    firstRun = false;   // Redundant???

                    double midwayPointX = (randomVertex.x + previousPoint.getPosition().x) / 2.0;
                    double midwayPointY = (randomVertex.y + previousPoint.getPosition().y) / 2.0;
                    midwayPoint = Point(midwayPointX, midwayPointY);
                    previousPoint = midwayPoint;

                    // We have the midway point, so adding it to the vector now
                    pointsToDraw.push_back(previousPoint);

                    counter++;  // May need this later






                }

                
                
            }

        }




        // Printing out everything in the vectors
        // ---------------------------------------------------------------------
        
        
        // If you use index < 5 it gives out of range error. Dont really know why
        for (int index = 0; index < pentagonVertexList.size(); index++)
        {
            //window.draw(pentagonVertexList[index]);
            window.draw(pentagonVertexList.at(index));
        }
           
        /*
        // Does same as above loop
        for (RectangleShape point : pentagonVertexList)
        {
            window.draw(point);
        }
        */
        



        //window.clear(); //
        elapsedTime += 1 * deltaTime.asSeconds();
        if (elapsedTime >= nextTimeToDraw)
        {
            nextTimeToDraw = drawingRate + elapsedTime;

            // CURRENTLY PRINTING HERE
            //window.clear();
            for (auto& point : pointsToDraw)
            {
                //point.setFillColor(color);
                window.draw(point);
            }
        }
        window.display();
        // ----------------------------------------------------------------------------


    }   // end main while loop



        
       

























    return 0;

}








// -----------------------------------------
// -----------------------------------------


int main9() // SQUARE
{
    bool changed = false;   // Probably delete
    srand(time(0));

    // Defines the rate of drawing in seconds. Decreasing this value will make the drawing process
    // slower a little bit. But you will see many points drawn in realtime.
    float drawingRate = 0.1;    // was 0.5
    float nextTimeToDraw = 0;
    double elapsedTime = 0;

    Clock clock;

    int screenRes_X = 1920;
    int screenRes_Y = 1080;

    VideoMode videoModeObject(screenRes_X, screenRes_Y);
    RenderWindow window(videoModeObject, "Chaos Game", Style::Default);

    RectangleShape myShape;

    Vector2f size;      // my more wordy way of doing it
    size.x = 3;
    size.y = 3;

    ShapeType shapeType = ShapeType::SQUARE;

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

    int counter = 0;    // DELETE LATER
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
            cout << "berry1" << endl;
            if (event.type == Event::MouseButtonPressed)
            {
                cout << "berry2" << endl;
                if (event.mouseButton.button == Mouse::Left)
                {
                    cout << "berry3" << endl;
                    isLeftMouseButtonPressed = true;
                }
            }
        }

        if (isLeftMouseButtonPressed == true)
        {
            //mousePosition = Mouse::getPosition(window);   //Ahmed's way

            mousePosition.x = event.mouseButton.x;          //My way
            mousePosition.y = event.mouseButton.y;
        }

            // Draw the starting square and display it on the screen
            vector<RectangleShape> squareVertexList;
            squareVertexList = drawSquare(window);
            window.display();

            if (starterPoint.getPosition() == Vector2f(0, 0))   // If user has not yet clicked somewhere inside the square
            {
                //cout << "Raisin0" << endl;

                if (isLeftMouseButtonPressed)     // Then, when they do click, make a note of where it was.
                {
                    mousePosition = Mouse::getPosition(window);
                    starterPoint = Point(mousePosition.x, mousePosition.y);
                    previousPoint = starterPoint;                               
                }


            }

            else
            {
                if (firstRun == true)   // If this is the first run, make sure the "last vertex" is arbitrarily set to something.
                {
                    //cout << "Raisin" << endl;

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
                    firstRun = false;
                }
                
                // If this is not the first run, choose a random vertex and then find the midway point between it, and the previous point. Afterwards, 
                // set this midway point to be the previous point once you have used it.
                else
                {
                    //cout << "Raisin3" << endl;


                    //randomVertex = randomVertexButNotSameAsLast(squareVertexList, lastVertexIndex); // While this is not returning lastVertexPos
                    randomVertex = randomVertexPositionSquare(squareVertexList); // While this is not returning lastVertexPos
                    while (randomVertex == lastVertexPos)
                    {
                        randomVertex = randomVertexPositionSquare(squareVertexList); // Trying again
                    }

                    //lastVertexIndex = randomVertex;
                    //cout << "random vertex x: " << randomVertex.x << endl;
                    //cout << "random vertex y : " << randomVertex.y << endl << endl;

                    lastVertexPos = randomVertex; 
                    firstRun = false;

                    //cout << lastVertexPos.x << endl << lastVertexPos.y << endl << endl;

                    
                    double midwayPointX = (randomVertex.x + previousPoint.getPosition().x ) / 2.0;
                    double midwayPointY = (randomVertex.y + previousPoint.getPosition().y ) / 2.0;
                    midwayPoint = Point(midwayPointX, midwayPointY);
                    previousPoint = midwayPoint;

                    //cout << "midwayPoint: " << midwayPoint.getPosition().x << endl;

                    pointsToDraw.push_back(previousPoint);

                    //cout << pointsToDraw[counter].getPosition().x << endl << endl;
                    //cout << "size: " << pointsToDraw.size();
                    counter++;




                }               
                
           
                
            }
            
            
       

            //window.draw(shapeVertices[0]);

            /*
            for (int index = 0; index < 3; index++)
            {
                window.draw(shapeVertices[index]);

            }
            */

            Color color;
            //color.r = 200;
            Color color2;
            color2.r = 200;
            
            if (changed == false)
            {
                color.r = 80;
                color.b = 200;
            }

            



            // EXPERIMENTAL ---------------------------------------------------------------------------------
            /*
            while (window.pollEvent(event))
            {
                //cout << "HERE";
                if (event.type == Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        isLeftMouseButtonPressed = true;
                    }
                }
            }

            if (isLeftMouseButtonPressed)
            {
                color = color2; 
                changed = true;

                mousePosition = Mouse::getPosition(window);
                double radius = 200;
                /*
                for (auto& point : pointsToDraw)
                {
                    //if ( (point.getPosition().y - mousePosition.y) < radius)
                    //{
                    window.clear();
                    //point.setFillColor(color2);
                    //color = color2;
                    //window.draw(point);
                    //}

                }
                window.display();
                
            }
            */
            

            // ----------------------------------------------------------------------------------------




            //window.clear(); //
            elapsedTime += 1 * deltaTime.asSeconds();
            //if (elapsedTime >= nextTimeToDraw)
            //{
                nextTimeToDraw = drawingRate + elapsedTime;

                // CURRENTLY PRINTING HERE
                //window.clear();
                for (auto& point : pointsToDraw)
                {
                    point.setFillColor(color);
                    window.draw(point);
                }
                window.display();




                /*
                // HIGHLY EXPERIMENTAL --------------------------------------------------
                if (isLeftMouseButtonPressed)
                {
                    cout << "GOOD";
                    mousePosition = Mouse::getPosition(window);
                    double radius = 200;
                    for (auto& point : pointsToDraw)
                    {
                        //if ( (point.getPosition().y - mousePosition.y) < radius)
                        //{
                            window.clear();
                            point.setFillColor(color);
                            window.draw(point);
                        //}

                    }
                    window.display();
                }
                // -----------------------------------------------------------------------------------------
                */
            //}

    } //end while loop

    /*
    cout << endl << "END " << endl;
    cout << pointsToDraw.size();
    for (auto& point : pointsToDraw)
    {
        cout << point.getPosition().x << endl << point.getPosition().y << endl << endl;
        cout << "dsfdsf" << endl;
        window.draw(point);
    }
    window.display();
    */



    // JUST A TEST DISPLAY TO SEE IF IT IS RECORDING THE POSIOTION OF THE 3 ORIGINAL VERTICES
    /*
    for (int index = 0; index < 3; index++)
    {
        Vector2f temp;
        temp = shapeVertices[index].getPosition();
        cout << "x: " << temp.x << endl << "y: " << temp.y << endl;

    }
    */
    


    return 0;
}




// ---------------------------------------------------------------------
// ---------------------------------------------------------------------



int main2()
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
                cout << "ORANGE" << endl;
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
                    cout << "APPLE" << endl;
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
                    cout << "PEAR" << endl;
                    Vector2f randomVertex = RandomVertexPosition(shapeVertices);

                    // Ask question about this syntax
                    Vector2f midwayPointPosition = Vector2f((randomVertex.x + previousPoint.getPosition().x) / 2.0, (randomVertex.y + previousPoint.getPosition().y) / 2.0);

                    midwayPoint = Point(midwayPointPosition.x, midwayPointPosition.y);

                    previousPoint = midwayPoint;

                    pointsToDraw.push_back(previousPoint);
                }
            }
        }

        /*********** We'll probably need another algorithm for a pentagon shape fractal **************/

        /*********** We'll probably need another algorithm for a square shape fractal ***************/

        /**************** Clear and Draw all points ********************/

        // Draw all shape vertices.
        if (starterPoint.getPosition() == Vector2f(0, 0))
        {
            window.clear();
            for (RectangleShape vertex : shapeVertices)
            {
                window.draw(vertex);
                cout << "HERE";
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

            for (int i = 0; i < (int)pointsToDraw.size(); i++)
            {
                window.draw(pointsToDraw[i]);
                pointsCount++;
            }

            window.display();

            cout << "Number of points drawn: " << pointsCount << endl;
        }
    }

    return 0;
}
