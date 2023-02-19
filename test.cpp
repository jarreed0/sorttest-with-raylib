#include <chrono>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

struct Point {
    int x;
    int y;
};

// Solution 1: using std::sort with a custom comparison function
void sort_points_with_sort(std::vector<Point>& points) {
    std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return a.y > b.y;
    });
}

// Solution 2: using iterators and std::vector::erase
/*void sort_points_with_iterators(const std::vector<Point>& points, std::vector<Point>& sorted_points) {
    while (!points.empty()) {
        auto highest_y_point_iter = points.begin();
        for (auto it = points.begin(); it != points.end(); ++it) {
            if (it->y > highest_y_point_iter->y) {
                highest_y_point_iter = it;
            }
        }
        sorted_points.push_back(std::move(*highest_y_point_iter));
        points.erase(highest_y_point_iter);
    }
}*/
void sort_points_with_iterators(const std::vector<Point>& input_points, std::vector<Point>& output_points) {
    // Create a non-const copy of the input vector
    std::vector<Point> points = input_points;

    // Sort the vector by y-coordinate in descending order
    std::sort(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
        return p1.y > p2.y;
    });

    // Copy the sorted points to the output vector
    output_points.clear();
    output_points.reserve(points.size());
    for (const auto& point : points) {
        output_points.push_back(point);
    }
}


// Solution 3: using std::max_element and std::vector::erase
/*void sort_points_with_max_element(const std::vector<Point>& points, std::vector<Point>& sorted_points) {
    while (!points.empty()) {
        auto it = std::max_element(points.begin(), points.end(), [](const Point& a, const Point& b) {
            return a.y < b.y;
        });
        sorted_points.push_back(std::move(*it));
        points.erase(it);
    }
}*/
void sort_points_with_max_element(const std::vector<Point>& input_points, std::vector<Point>& output_points) {
    // Create a non-const copy of the input vector
    std::vector<Point> points = input_points;

    // Sort the vector by y-coordinate in descending order
    std::sort(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
        return p1.y > p2.y;
    });

    // Copy the sorted points to the output vector
    output_points.clear();
    output_points.reserve(points.size());
    while (!points.empty()) {
        // Find the highest-y point and copy it to the output vector
        auto it = std::max_element(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
            return p1.y < p2.y;
        });
        output_points.push_back(*it);

        // Remove the highest-y point from the input vector
        points.erase(it);
    }
}

// Solution 4: using a for loop and std::vector::erase
void sort_points_with_for_loop(const std::vector<Point>& input_points, std::vector<Point>& output_points) {
    // Create a non-const copy of the input vector
    std::vector<Point> points = input_points;

    // Sort the vector by y-coordinate in descending order
    std::sort(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
        return p1.y > p2.y;
    });

    // Copy the sorted points to the output vector
    output_points.clear();
    output_points.reserve(points.size());
    while (!points.empty()) {
        // Find the highest-y point and copy it to the output vector
        int highest_y_index = 0;
        for (int i = 1; i < points.size(); i++) {
            if (points[i].y > points[highest_y_index].y) {
                highest_y_index = i;
            }
        }
        output_points.push_back(points[highest_y_index]);

        // Remove the highest-y point from the input vector
        points.erase(points.begin() + highest_y_index);
    }
}

void sort_points_with_loop(std::vector<Point>& points) {
    std::vector<Point> sorted_points;
    // Manually sort the vector by y-coordinate and save the result to the temporary vector
    while (!points.empty()) {
        // Find the point with the highest y-coordinate
        Point highest_y_point = points[0];
        size_t highest_y_index = 0;
        for (size_t i = 1; i < points.size(); ++i) {
            if (points[i].y > highest_y_point.y) {
                highest_y_point = points[i];
                highest_y_index = i;
            }
        }
        // Move the highest y-coordinate point to the temporary vector
        sorted_points.push_back(std::move(highest_y_point));
        // Erase the highest y-coordinate point from the original vector
        points.erase(points.begin() + highest_y_index);
    }
    points = sorted_points;
}


/*void sort_points_with_for_loop(const std::vector<Point>& points, std::vector<Point>& sorted_points) {
    while (!points.empty()) {
        Point highest_y_point = points[0];
        size_t highest_y_index = 0;
        for (size_t i = 1; i < points.size(); ++i) {
            if (points[i].y > highest_y_point.y) {
                highest_y_point = points[i];
                highest_y_index = i;
            }
        }
        sorted_points.push_back(std::move(highest_y_point));
        points.erase(points.begin() + highest_y_index);
    }
}*/

// Solution 5: using std::priority_queue
void sort_points_with_priority_queue(const std::vector<Point>& points, std::vector<Point>& sorted_points) {
    std::priority_queue<Point, std::vector<Point>, std::function<bool(const Point&, const Point&)>> pq(
        [](const Point& a, const Point& b) {
            return a.y < b.y;
        }
    );
    for (const auto& p : points) {
        pq.push(p);
    }
    while (!pq.empty()) {
        sorted_points.push_back(pq.top());
        pq.pop();
    }
}

int main() {
    const int n = 10000;
    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        points[i] = { i, n - i };
    }

    std::vector<Point> sorted_points;

    // Time solution 1
    auto start_time = std::chrono::high_resolution_clock::now();
    sorted_points = points;
    sort_points_with_sort(sorted_points);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Solution 1 (std::sort): " << duration1.count() << " microseconds" << std::endl;

    // Time solution 2
    start_time = std::chrono::high_resolution_clock::now();
    sort_points_with_iterators(points, sorted_points);
    end_time = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Solution 2 (iterators): " << duration2.count() << " microseconds" << std::endl;

    // Time solution 3
    start_time = std::chrono::high_resolution_clock::now();
    sort_points_with_max_element(points, sorted_points);
    end_time = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Solution 3 (std::max_element): " << duration3.count() << " microseconds" << std::endl;

    // Time solution 4
    start_time = std::chrono::high_resolution_clock::now();
    sort_points_with_for_loop(points, sorted_points);
    end_time = std::chrono::high_resolution_clock::now();
    auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Solution 4 (for loop): " << duration4.count() << " microseconds" << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    sort_points_with_loop(points);
    end_time = std::chrono::high_resolution_clock::now();
    auto duration42 = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Solution 4.2 (for loop): " << duration42.count() << " microseconds" << std::endl;

    // Time solution 5
    start_time = std::chrono::high_resolution_clock::now();
    sort_points_with_priority_queue(points, sorted_points);
    end_time = std::chrono::high_resolution_clock::now();
    auto duration5 = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Solution 5 (std::priority_queue): " << duration5.count() << " microseconds" << std::endl;

    // Print memory usage
    std::cout << "Memory usage: " << sizeof(points[0]) * points.size() << " bytes" << std::endl;

    return 0;
}
