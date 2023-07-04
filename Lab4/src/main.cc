

#include <iostream>
#include <fstream>
#include <sstream>
#include "geom.h"
#include "point.h"
#include "circle.h"
#include "polygon.h"
#include "reuleauxtriangle.h"
#include "sphere.h"
#include "cube.h"
#include "reuleauxtetrahedron.h"
using namespace std;
#define USAGE "USAGE %s test-file\n"

/*largely influenced by lectures regarding Lab4*/
static Point2D getPoint(string &token)
{
    double x,y;
    stringstream vstream(token);
    string value;
    if(getline(vstream, value, ','))
    {
        stringstream(value) >> x;
        if(getline(vstream, value, ','))
        {
            stringstream(value) >> y;
            return Point2D(x,y);
        }
    }
    throw "invalid point " + token;
}

static double getRadius(string &token)
{
    return stod(token);
}

static Point3D getPoint3D(string &token)
{
    double x,y,z;
    stringstream vstream(token);
    string value;
    if(getline(vstream, value, ','))
    {
        stringstream(value) >> x;
        if(getline(vstream, value, ','))
        {
            stringstream(value) >> y;
            if(getline(vstream, value, ','))
            {
                stringstream(value) >> z;
                return Point3D(x,y,z);
            }
        }
    }
    throw "invalid point " + token;
}

static void parse(const string line)
{
	stringstream stream(line);
    string token;

    Circle *innerCirc = NULL;
    Circle *outerCirc = NULL;
    bool innCirc = false;
    bool outCirc = false;

    RegularConvexPolygon *innerP = NULL;
    RegularConvexPolygon *outerP = NULL;
    bool innP = false;
    bool outP = false;

    ReuleauxTriangle *innerRt = NULL;
    ReuleauxTriangle *outerRt = NULL;
    bool innRt = false;
    bool outRt = false;

    Sphere *innerS = NULL;
    Sphere *outerS = NULL;
    bool innS = false;
    bool outS = false;

    ReuleauxTetrahedron *innerRtet = NULL;
    ReuleauxTetrahedron *outerRtet = NULL;
    bool innRtet = false;
    bool outRtet = false;

    Cube *innerCube = NULL;
    Cube *outerCube = NULL;
    bool innCube = false;
    bool outCube = false;

    bool expected = false;
    bool got = false;

	while(stream >> token)
	{
        if (token == "Circle")
		{
            stream >> token;
            Point2D center = getPoint(token);
            stream >> token;
            double radius = getRadius(token);
            if(innerCirc == NULL && innerP == NULL && innerRt == NULL)
            {
                innerCirc = new Circle (center, radius);
                innCirc = true;
            }
            else
            {
                outerCirc = new Circle(center, radius);
                outCirc = true;
            }
            if(token == "true")
            {
                expected = true;
            }
        }

        if (token == "RegularConvexPolygon")
        {
            vector<Point2D> vertexP;
            while(token != "true" || "false" || "Circle" || "RegularConvexPolygon" || "ReuleauxTriangle" || "ReuleauxTetrahedron" || "Cube" || "Sphere")
            {
                stream >> token;
                vertexP.push_back(getPoint(token));
                stream >> token;
            }
            if(innerP == NULL && innerCirc == NULL && innerRt == NULL)
            {
                innerP = new RegularConvexPolygon (vertexP);
                innP = true;
            }
            else
            {
                outerP = new RegularConvexPolygon (vertexP);
                outP = true;
            }
            if(token == "true")
            {
                expected = true;
            }
        }

        if (token == "ReuleauxTriangle")
        {
            int i = 0;
            Point2D vertexRt[3];
            while(i < 3)
            {
                stream >> token;
                vertexRt[i] = (getPoint(token));
                stream >> token;
                i++;
            }
            if(innerRt == NULL && innerCirc == NULL && innerP == NULL)
            {
                innerRt = new ReuleauxTriangle (vertexRt);
                innRt = true;
            }
            else
            {
                outerRt = new ReuleauxTriangle (vertexRt);
                outRt = true;
            }
            if(token == "true")
            {
                expected = true;
            }
        }

        if (token == "Sphere")
        {
            stream >> token;
            Point3D center = getPoint3D(token);
            stream >> token;
            double radius = getRadius(token);
            if(innerS == NULL && innerCube == NULL && innerRtet == NULL)
            {
                innerS = new Sphere (center, radius);
                innS = true;
            }
            else
            {
                outerS = new Sphere (center, radius);
                outS = true;
            }
            if(token == "true")
            {
                expected = true;
            }
        }

        if (token == "Cube")
        {
            int k = 0;
            int m = 0;
            Point3D vertexCU[4];
            Point3D vertexCL[4];
            while((k + m) <= 7)
            {
                stream >> token;
                if(k <= 3)
                {
                    vertexCU[k] = getPoint3D(token);
                    k++;
                }
                if(k > 3)
                {
                    vertexCL[m] = getPoint3D(token);
                    m++;
                }
                stream >> token;
            }
            if(innerS == NULL && innerCube == NULL && innerRtet == NULL)
            {
                innerCube = new Cube (vertexCL, vertexCU);
                innCube = true;
            }
            else
            {
                outerCube = new Cube (vertexCL, vertexCU);
                outCube = true;
            }
            if(token == "true")
            {
                expected = true;
            }
        }

        if (token == "ReuleauxTetrahedron")
        {
            int j = 0;
            Point3D vertexRtet[4];
            while(j < 4)
            {
                stream >> token;
                vertexRtet[j] = (getPoint3D(token));
                stream >> token;
                j++;
            }
            if(innerS == NULL && innerCube == NULL && innerRtet == NULL)
            {
                innerRtet = new ReuleauxTetrahedron (vertexRtet);
                innRtet = true;
            }
            else
            {
                outerRtet = new ReuleauxTetrahedron (vertexRtet);
                outRtet = true;
            }
            if(token == "true")
            {
                expected = true;
            }
        }

        if(innCirc == true && outCirc == true)
        {
            got = innerCirc->containedWithin(*outerCirc);
        }
        if(innCirc == true && outP== true)
        {
            got = innerCirc->containedWithin(*outerP);
        }
        if(innCirc == true && outRt == true)
        {
            got = innerCirc->containedWithin(*outerRt);
        }


        if(innP == true && outP== true)
        {
            got = innerP->containedWithin(*outerP);
        }
        if(innP == true && outCirc == true)
        {
            got = innerP->containedWithin(*outerCirc);
        }
        if(innP == true && outRt == true)
        {
            got = innerP->containedWithin(*outerRt);
        }


        if(innRt == true && outRt == true)
        {
            got = innerRt->containedWithin(*outerRt);
        }
        if(innRt == true && outCirc == true)
        {
            got = innerRt->containedWithin(*outerCirc);
        }
        if(innRt== true && outP == true)
        {
            got = innerRt->containedWithin(*outerP);
        }

        
        if(innS == true && outS == true)
        {
            got = innerS->containedBy(*outerS);
        }
        if(innS == true && outCube== true)
        {
            got = innerS->containedBy(*outerCube);
        }
        if(innS == true && outRtet == true)
        {
            got = innerS->containedBy(*outerRtet);
        }


        if(innCube == true && outCube== true)
        {
            got = innerCube->containedBy(*outerCube);
        }
        if(innCube == true && outS == true)
        {
            got = innerCube->containedBy(*outerS);
        }
        if(innCube == true && outRt == true)
        {
            got = innerCube->containedBy(*outerRtet);
        }


        if(innRtet == true && outRtet == true)
        {
            got = innerRtet->containedBy(*outerRtet);
        }
        if(innRtet == true && outS == true)
        {
            got = innerRtet->containedBy(*outerS);
        }
        if(innRtet == true && outCube == true)
        {
            got = innerRtet->containedBy(*outerCube);
        }
        cout << (got == expected ? "PASS" : "FAIL") << endl;
	}
}

int main(int argc, char *argv[]) 
{
    if (argc < 2)
    {
        printf(USAGE, argv[0]);
        return -1;
    }
    
    std::ifstream ifs(argv[1]);
    if(ifs)
    {
    	string line;
    	while(getline(ifs, line))
    	{
    		parse(line);
    	}
    }
    return 0;
}