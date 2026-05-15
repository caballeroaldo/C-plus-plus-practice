#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

struct Point {
    double x;
    double y;
};

struct Observation {
    int frameNumber;
    Point position;
};

struct Track {
    int id;
    Point position;
    int missedFrames;
    vector<Observation> history;
};

double squaredDistance(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main() {    
    // Initialize Tracks
    vector<Track> tracks;
    int nextTrackId = 0;

    const double distanceThreshold = 1000; // Squared Distance not 1000 pixels
    const int maxMissedFrames = 3;

    int frameNumber = 1;

    // Read the first frame
    int numDetections;
    cout << "How many detections in frame 1? ";
    cin >> numDetections;

    vector<Point> frame1;
    for (int i = 0; i < numDetections; i++) {
            Point p;
            cout << "Enter point " << i + 1 << " (x y): ";
            cin >> p.x >> p.y;
            frame1.push_back(p);
    }

    // Initialize frame1 into track
    for(const Point& p: frame1) {
        tracks.push_back({nextTrackId++, p, 0});
    }

    frameNumber++;

    // loop through detections to get additional frames
    while(true) {
        cout << "How many detections in frame " << frameNumber << "? ";
        cin >> numDetections;

        if (numDetections == 0) {
            cout << "No more frames, Exiting. \n";
            break;
        }

        vector<Point> currentFrame;
        for (int i = 0; i < numDetections; i++) {
            Point p;
            cout << "Enter point " << i + 1 << " (x y): ";
            cin >> p.x >> p.y;
            currentFrame.push_back(p);
        }

        vector<bool> trackUsed(tracks.size(), false);

        // match detections to tracks: greedy implementation
        for (const Point& p : currentFrame) {
            double minDist = numeric_limits<double>::max();
            int bestTrackIndex = -1;
            for (int j = 0; j < tracks.size(); j++) {
                if (trackUsed[j]) continue;
                double dist = squaredDistance(p, tracks[j].position);
                if (dist < minDist) {
                    minDist = dist;
                    bestTrackIndex = j;
                }
            }
            if (bestTrackIndex != -1 && minDist < distanceThreshold) {
                // Match to existing track
                tracks[bestTrackIndex].position = p;
                tracks[bestTrackIndex].missedFrames = 0;
                tracks[bestTrackIndex].history.push_back({frameNumber, p});
                trackUsed[bestTrackIndex] = true;
                cout << "Matched point (" << p.x << ", " << p.y << ") to Track " << tracks[bestTrackIndex].id << "\n";
            } else {
                // Create a new track
                Track newTrack;
                newTrack.id = nextTrackId++;
                newTrack.position = p;
                newTrack.missedFrames = 0;
                newTrack.history.push_back({frameNumber, p});

                tracks.push_back(newTrack);
                trackUsed.push_back(true);
                cout << "Created new Track " << newTrack.id << " for point (" << p.x << ", " << p.y << ")\n";
            }
        }

        // update missedFrames
        for (int i = 0; i < tracks.size(); i++) {
            if (!trackUsed[i]) {
                tracks[i].missedFrames++;
            } else {
                tracks[i].missedFrames = 0;
            }
        }

        // delete stale tracks 
        // Checking it by looping backwards
        // Side note: Added static_cast to avoid unsigned type bug
        for (int i = static_cast<int>(tracks.size()) - 1; i >= 0; i--) {
            if (tracks[i].missedFrames > maxMissedFrames) {
                cout << "Deleting track " << tracks[i].id << " due to inactivity.\n"; 
                tracks.erase(tracks.begin() + i);
            }
        }


        cout << "\nCurrent tracks:\n";
        for (const Track& t : tracks) {
            cout << "Track " << t.id << " -> ("
                 << t.position.x << ", " << t.position.y
                 << "), missedFrames=" << t.missedFrames << "\n";

            cout << "  Observation:\n";
            for (const Observation& obs: t.history) {
                cout << "    Frame " << obs.frameNumber << ": (" 
                    << obs.position.x << ", " 
                    << obs.position.y << ")\n";
            }
            cout << "\n";

            frameNumber++;
        }
    }


    return 0;
}