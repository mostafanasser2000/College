%
student(stud01, 'Programming 1', 90).
student(stud01, 'Math 1', 78).
student(stud01, 'Statistics 1', 94).
student(stud01, 'Electronics 1', 81).
student(stud01, 'Management', 66).
student(stud01, 'English', 83).
student(stud02, 'OS 1', 65).
student(stud02, 'Math 1', 50).
student(stud02, 'Data Communication', 76).
student(stud03, 'OOP', 68).
student(stud03, 'Math 1', 63).
student(stud03, 'Statistics 1', 98).
student(stud03, 'Electronics 2', 72).
student(stud04, 'Database', 59).
student(stud04, 'Math 3', 67).
student(stud04, 'Data Structures', 79).
student(stud05, 'Programming 1', 88).
student(stud05, 'Math 1', 75).
student(stud05, 'Statistics 1', 96).
student(stud05, 'Electronics 1', 89).
student(stud05, 'Management', 84).
student(stud06, 'Robotics', 62).
student(stud07, 'Programming 1', 50).
student(stud07, 'Math 2', 8).
student(stud07, 'Statistics 2', 70).
student(stud07, 'Electronics 1', 47).
student(stud08, 'OS 1', 71).
student(stud09, 'Robotics', 29).
student(stud09, 'Database', 57).
student(stud10, 'Data Structures', 82).
student(stud10, 'Math 2', 64).
student(stud10, 'Data Communication', 85).
student(stud10, 'Database', 46).
student(stud10, 'Electronics 2', 58).
student(stud10, 'Statistics 2', 97).
%
prerequisite('Programming 1', 'OOP').
prerequisite('OOP', 'OS 1').
prerequisite('OS 1', 'OS 2').
prerequisite('OOP', 'Data Structures').
prerequisite('Data Structures', 'Algorithms').
prerequisite('Algorithms', 'Advanced Algorithms').
prerequisite('Math 1', 'Math 2').
prerequisite('Math 2', 'Math 3').
prerequisite('Math 3', 'Math 4').
prerequisite('Statistics 1', 'Statistics 2').
prerequisite('Electronics 1', 'Electronics 2').
prerequisite('Electronics 2', 'Computer Architecture').
prerequisite('Computer Architecture', 'Microprocessors').
prerequisite('Data Communication', 'Networks').
prerequisite('Database', 'Data Warehouses').

%task1
member(X,[X|_]).
member(X,[_|T]) :-
       member(X,T).

studentsInCourse(Course,List) :-
    studentsInCourse(Course,[],List).

studentsInCourse(Course,TempList,List) :-
    student(ID,Course,GPA), 
	not(member([ID,GPA],TempList)), !,
    append([[ID,GPA]],TempList,NewList),
    studentsInCourse(Course, NewList,List).

studentsInCourse(_,List,List).

%task2
length_of_list([],0).

length_of_list([H|T],N) :-
    length_of_list(T,N1),
    N is N1+1.
    
numStudents(Course,N) :-
    studentsInCourse(Course,List),
    length_of_list(List,N).


%task3

max_of_list([],0).
max_of_list([H|T],MAX):- max_of_list(T,MAX1), H > MAX1,
    MAX is H.
max_of_list([H|T],MAX):- max_of_list(T,MAX1), H =< MAX1,
    MAX is MAX1.

get_students_grades(Student,List) :-
    get_students_grades(Student,[],List).

get_students_grades(Student,TempList,List) :-
    student(Student,_,Grade),
    not(member(Grade,TempList)), !,
    append([Grade],TempList,NewList),
    get_students_grades(Student,NewList,List).

get_students_grades(_,List,List).
   

maxStudentGrade(Student,MAX) :-
    get_students_grades(Student,Grades),
    max_of_list(Grades,MAX).


%task4

digit(0,zero).
digit(1,one).
digit(2,two).
digit(3,three).
digit(4,four).
digit(5,five).
digit(6,six).
digit(7,seven).
digit(8,eight).
digit(9,nine).

convert_num_to_digit(Num,List) :-
    X is Num//10 , Y is (Num - X*10),
    digit(X,X1),digit(Y,Y1), 
    List = [X1,Y1].

gradeInWords(Student,Course,GradesInWords) :-
    student(Student,Course,Grade),
    convert_num_to_digit(Grade,GradesInWords).



%task5

remainingCourses(StudentNum,CourseName,CoursesList):-
	remainingCourses(StudentNum,CourseName,CoursesList,[]).
	
	
remainingCourses(StudentNum, CourseName, CoursesList, TempList):-
	CourseName \= firstCourse,
	prerequisite(PreCourse,CourseName),
	(student(StudentNum, PreCourse, Grade), 
	Grade >= 50 -> remainingCourses(StudentNum,  , CoursesList, TempList);
	append([PreCourse],TempList, NewList), 
	remainingCourses(StudentNum, PreCourse, CoursesList, NewList)).

remainingCourses(StudentNum, , TempList, TempList).
