/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>

using namespace std;

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
    V2D returnit;
    string line;
    vector<string> temp;
    ifstream myfile(filename);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            string str = "";
            size_t count = 0;
            for (char s : line) {
                count++;
                if (s != ' ' && s != ',') {
                    str += s;
                }
                if (s == ',' || count == line.length()) {
                    temp.push_back(str);
                    str.clear();
                }
            }
            returnit.push_back(temp);
            temp.clear();
        }
    }
    return returnit;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student) {
    // YOUR CODE HERE
    V2D returnit;
    for (unsigned int i = 0; i < cv.size(); i++) {
        if (cv[i].size() < 1) {
            break;
        }
        vector<string> temp;
        string course = cv[i][0];
        temp.push_back(course);                      // push valid course name
        for (unsigned int ii = 1; ii < cv[i].size(); ii++) {
            for (unsigned int j = 0; j < student.size(); j++) {
                string s = student[j][0];
                if (cv[i][ii] == s) {
                    for (unsigned int k = 1; k < student[j].size(); k++) {
                        if (student[j][k] == course) {
                            temp.push_back(s);
                            break;
                        }
                    }
                }
            }
        }
        if (temp.size() > 1) {
            returnit.push_back(temp);
        }
        temp.clear();
    }
    return returnit;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */

void print_graph(map<string, vector<string>> graph) {
    for (auto i=graph.begin(); i!=graph.end(); ++i){
        cout << (*i).first << ": ";
        vector<string> vec = (*i).second;
        for (unsigned j=0; j < vec.size(); j++){
            cout << vec[j] << " ";
        }
        cout << endl;
    }
    return;
}

void print_color(map<string, int> color) {
    for (auto i=color.begin(); i!=color.end(); ++i){
        cout << (*i).first << ": " << (*i).second << endl;
    }
    return;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 *
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 *
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 *
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value.
 *
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */

bool already_exists(vector<string> vec, string to_find) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        if (vec[i] == to_find) {
            return true;
        }
    }
    return false;
}

V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots)
{
    // Your code here!
    map<string, vector<string>> students;
    for (unsigned int i = 0; i < courses.size(); i++) {
        for (unsigned int j = 1; j < courses[i].size(); j++) {
            students[courses[i][j]].push_back(courses[i][0]);
        }
    }
    map<string, vector<string>> graph;
    map<string, int> color;
    for (unsigned int i = 0; i < courses.size(); i++) {
        graph[courses[i][0]] = vector<string>();
        color[courses[i][0]] = 0;
    }
    for (auto it : students) {
        for (unsigned int i = 0; i < it.second.size() - 1; i++) {
            for (unsigned int j = i + 1; j < it.second.size(); j++) {
                if (!already_exists(graph[it.second[i]],it.second[j])) {
                    graph[it.second[i]].push_back(it.second[j]);
                }
                if (!already_exists(graph[it.second[j]],it.second[i])) {
                    graph[it.second[j]].push_back(it.second[i]);
                }
            }
        }
    }
    // print_graph(graph);
    /*  
        CS386: CS500 CS395 
        CS395: CS577 CS591 CS386 CS500 
        CS500: CS577 CS386 CS395 
        CS577: CS591 CS500 CS395 
        CS591: CS577 CS395 
    */

    for (auto vertex : graph) {
        if (color[vertex.first] == 0) {
            color[vertex.first]++;
        }
        vector<string> temp = graph[vertex.first];
        int flag = 1;
        while (flag == 1) {
            flag = 0;
            for (unsigned int i = 0; i < temp.size(); i++) {
                if (color[vertex.first] == color[temp[i]]) {
                    color[vertex.first]++;
                    flag = 1;
                    break;
                }
            }
        }
    }
    // print_color(color);
    /*
        CS386: 1
        CS395: 2
        CS500: 3
        CS577: 1
        CS591: 2
    */
    
    V2D returnit;
    for (auto timeslot : timeslots){
        returnit.push_back(vector<string>{timeslot});
    }
    for (auto c : color) {
        size_t i = size_t(c.second);
        if (i <= timeslots.size()) {
            returnit[i - 1].push_back(c.first);
        } else {
            return V2D{vector<string>{"-1"}};    
        }   
    }
    // for (unsigned int i = 0; i < returnit.size(); i++) {
    //     for (unsigned int j = 0; j < returnit[i].size(); j++) {
    //         cout << returnit[i][j] << endl;
    //     }
    // }
    return returnit;
} 