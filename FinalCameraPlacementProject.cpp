#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

struct Camera {
    double x, y;
    double radius;
};

struct Region {
    double width, height;
};

bool isOverlap(const Camera& c1, const Camera& c2) {
    double dx = c1.x - c2.x;
    double dy = c1.y - c2.y;
    double distance = dx * dx + dy * dy;
    double radiiSum = (c1.radius + c2.radius) * (c1.radius + c2.radius);
    return distance < radiiSum;
}

bool isPointInCamera(const Camera& camera, double x, double y) {
    double dx = x - camera.x;
    double dy = y - camera.y;
    double distance = dx * dx + dy * dy;
    return distance <= camera.radius * camera.radius;
}

void inscribeHexagon(Camera& camera) {
    double sideLength = 2 * camera.radius;
    double hexagonRadius = (sideLength / 2) * sqrt(3);
    camera.radius = hexagonRadius;
}

void maximalIndependentSet(vector<Camera>& cameras) {
    vector<bool> selected(cameras.size(), true);

    for (size_t i = 0; i < cameras.size(); ++i) {
        if (selected[i]) {
            for (size_t j = i + 1; j < cameras.size(); ++j) {
                if (isOverlap(cameras[i], cameras[j])) {
                    selected[j] = false;
                }
            }
        }
    }

   
    cameras.erase(
        remove_if(cameras.begin(), cameras.end(), [&](const Camera& camera) {
            return !selected[&camera - &cameras[0]];
        }),
        cameras.end());
}

int main() {
    Region region = {100, 100};
    int numRows = 5;
    int numCols = 5;
    double radius = 10 / sqrt(3);

    vector<Camera> cameras;

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            double x = (i * region.width) / numRows + radius;
            double y = (j * region.height) / numCols + radius;
            cameras.push_back({x, y, radius});
        }
    }

    for (Camera& camera : cameras) {
        inscribeHexagon(camera);
    }

    maximalIndependentSet(cameras);

    for (size_t i = 0; i < cameras.size(); ++i) {
        cout << "Camera " << i + 1 << ": (" << cameras[i].x << ", " << cameras[i].y << "), Radius: " << cameras[i].radius << endl;
    }

    return 0;
}
