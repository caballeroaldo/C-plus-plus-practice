#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
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
        {300, 400},
        {498, 502}
    };

    // Frame 2
    vector<Point> frame2 = {
        {105, 205},
        {298, 398},
        {500, 500}
    };
    // Initialize Tracks
    vector<Track> tracks;

    for (int i = 0; i < frame1.size(); i++) {
        tracks.push_back({i, frame1[i]});
    }

    // Match frames using tracks 
    cout << "Matching frame 2 to frame 1...\n";

    vector<bool> trackUsed(tracks.size(), false);
    double distanceThreshold = 1000;
    int nextTrackId = tracks.size();

    for (const Point& p : frame2) {
        double minDist = numeric_limits<double>::max();
        int bestTrackIndex = -1;

        for(int j = 0; j < tracks.size(); j++) {
            if (trackUsed[j]) continue;

            double dist = squaredDistance(p, tracks[j].position);

            if (bestTrackIndex == -1 || dist < minDist) {
                minDist = dist;
                bestTrackIndex = j;
            }
        }

        // Update track position and accounts for the threshold for considering it as another object
        if (bestTrackIndex != -1 && minDist < distanceThreshold) {
            tracks[bestTrackIndex].position = p;
            trackUsed[bestTrackIndex] = true;

            cout << "Matched point (" << p.x << ", " << p.y << ") to Track " << tracks[bestTrackIndex].id << "\n"; 
        } else {
            // No good match, make a new track
            Track newTrack;
            newTrack.id = nextTrackId++;
            newTrack.position = p;

            tracks.push_back(newTrack);
            trackUsed.push_back(true);

            cout << "Created new Track " << newTrack.id << " for point (" << p.x << ", " << p.y << ")\n";
        }
    }

    cout << "Total tracks: " << tracks.size() << "\n";
    cout << "\nFinal tracked Positions:\n";
    for (const Track& t: tracks) {
        cout << "Track " << t.id << " -> (" << t.position.x << ", " << t.position.y << ")\n";
    }

    return 0;
}