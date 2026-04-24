#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Point {
    double x;
    double y;
};

struct Track {
    int id;
    Point position;
};

double squaredDistance(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main() {
    // Frame 1
    vector<Point> frame1 = {
        {100, 200},
        {300, 400}
    };

    // Frame 2
    vector<Point> frame2 = {
        {105, 205},
        {298, 398}
    };
    // Initialize Tracks
    vector<Track> tracks;

    for (int i = 0; i < frame1.size(); i++) {
        tracks.push_back({i, frame1[i]});
    }

    // Match frames using tracks 
    cout << "Matching frame 2 to frame 1...\n";

    for (const Point& p : frame2) {
        double minDist = squaredDistance(p, tracks[0].position);
        int bestTrackIndex = 0;

        for(int j = 0; j < tracks.size(); j++) {
            double dist = squaredDistance(p, tracks[j].position);

            if (dist < minDist) {
                minDist = dist;
                bestTrackIndex = j;
            }
        }
        // Update track position
        tracks[bestTrackIndex].position = p;
    }

    for (const Track& t: tracks) {
        cout << "Track " << t.id << " -> (" << t.position.x << ", " << t.position.y << ")\n";
    }

    return 0;
}