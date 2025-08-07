#ifndef STUDENTS_HPP
# define STUDENTS_HPP

#include <iostream>
#include <fstream> 
#include <sstream>
#include <utility>
#include <string>
#include <map>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <random>

//Paths de los ficheros de instancia (students.csv) y solución actual (solution.csv)
#define PATH_INSTANCE "../../data/students.csv"
#define PATH_SOLUTION "../../data/solution.csv"

//Dimensiones del problema (la cantidad de estudiantes será N_CLUSTERS*N_ROWS*N_SEATS)
#define N_CLUSTERS 4
#define N_ROWS 8
#define N_SEATS 6

//Máximo radio a considerar en las preferencias con respecto a otros estudiantes
#define MAX_RADIO 4

class Student
{
private:
    int		pref_cluster;
    int		pref_row;
    int		pref_seat;
    int	    other_id_1;
    int     other_id_2;
public:
    Student();
    Student(int pref_c, int pref_r, int pref_s, int o_id1, int o_id2);
    void get_seat_preference(int *cluster, int *row, int *seat);
    void get_student_preference(int *id1, int *id2);
};

class Location
{
private:
    int		final_cluster;
    int		final_row;
    int		final_seat;
public:
    Location();
    int sit_down(int cluster, int row, int seat);
    void get_seat(int *cluster, int *row, int *seat);
};

class USP
{
private:
    int     n_students;
    int		n_clusters;
    int		n_rows;
    int		n_seats;
    std::map<int,Student> instance;
    std::map<int,Location> solution;
    std::map<std::string,int> seats;

public:
    USP(int n_c, int n_r, int n_s, std::string instance_path);
    void                        get_dimensions(int *n_clusters, int *n_rows, int *n_seats);
    int                         get_size();
    int                        get_seat_preference(int id, int *pref_cluster, int *pref_row, int *pref_seat);
    int                        get_student_preference(int id, int *other_id_1, int *other_id_2);
    int                        sit_down(int id, int cluster, int row, int seat);
    int                        get_seat(int id, int *cluster, int *row, int *seat);
    int                         get_student_in_seat(int cluster, int row, int seat);
    int                         evaluate();
    int                         print_solution(std::string solution_path);

};

#endif