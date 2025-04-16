/*
 * Name = yazan AboAlown
 * ID = 121045
 * Section : 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//the student dataType that includes its properties

typedef struct {

    int id;
    char name[20];
    char address[20];
    int classID;
    char date[20];

} Student;

//the ADT of the LinkedList that includes its properties

struct node {
    Student data;
    struct node* next;
};
//the ADT of the Binary Search Tree that includes its properties
struct Bnode {

    Student data;
    struct Bnode* left;
    struct Bnode* right;
};

typedef struct Bnode* Tree;

//Binary search tree funcitons as well as general ones
Tree insertT (Tree t, Student S); //inserts a node of type student to the tree
void printTree (Tree t); //prints the contents of the tree
Tree findT (Tree t, int data); //Searches for a node
Tree findMin (Tree t); //finds the minimum value
Tree deleteT (Tree t, Student s); //deletes a node
void printStudent (Student s); //prints student information
void insertAndSort (struct node* list, Student s); //insert and presort
Tree deleteTid (Tree t, int id); //deletes a node with a given ID.
void loadFromFile (FILE *p, struct node *list, Tree *t); //load the contents of a file.
void printStudentFile (FILE *p, Student s); //Prints student information into a file.
void printListFile(struct node* L, FILE *q); //Prints list information into a file.

//Linked list functions
struct node* makeEmpty(struct node* L); //creates a list
void deleteList(struct node* L); //deletes a list
int isEmpty(struct node* L); //checks the emptiness of a list.
void printList(struct node* L); //prints the contents of a list.
void addFirst (struct node* L, Student data); //adds an element to the start of a list.
struct node* findPrevious_int (struct node* L, int id); //finds the element before the inserted one.
void remove_int (struct node* L, int id); //removes an element given the ID.
void addAfter (struct node *list, struct node* ptr, Student data); //adds an element after the pointer given as input.


int main() {

    char name[20] ,address[20], date[20];
    int number, id, classID;

    Tree t = NULL;

    struct node *list = NULL;
    list = makeEmpty(list);

    //reads and loads a file if it exists
    FILE *p = fopen("../students.data", "r");


    if (p!=NULL) {
        loadFromFile(p, list, &t); //loads the contents of the file and fills the list and the tree
        fclose(p);
    }
    else {
        printf("File not found!\n");
    }

    //loop that controls the menu
    for (;;) {

        printf("-----School Information Program----\n\n");
        printf("What do you want to do?\n\n");

        printf("1) Insert a student with all its associated data. \n"
               "2) Find a student by his/her student ID, \n"
               "3) List all students in lexicographic order of their names\n"
               "4) Search for a city and list all students from that city in lexicographic order of their names.\n"
               "5) List all students by their class in lexicographic order of their names.\n"
               "6) Delete a student given his/her student ID. \n"
               "7) Save all students in file students.data. \n"
               "8) Exit.\n");

        printf("Enter the number corresponding to each operation.\n");

        scanf("%d", &number); //controls the operation chosen.

        switch (number) {

            //Option 1 : adding a student to the system.
            case 1:


                printf("Enter the student information in the following order :\n "
                       "id, name, address, classID, date (DD/MM/YYYY)\n");

                scanf("%d%s%s%d%s", &id, name, address, &classID, date);
                Student s = {.id= id, .classID = classID};

                strcpy(s.name, name);
                strcpy(s.address, address);
                strcpy(s.date, date);


                Tree findStat = findT(t, id); //checks if a given ID already exists.

                if (t == NULL) {
                    t = insertT(t, s);
                } else {
                    insertT(t, s);
                }

                if (findStat == NULL) {
                    insertAndSort(list, s);
                } else {
                    printf("This ID already exists.\n\n");
                }
                break;

                //Option 2 : Finding a student by his/her ID.
            case 2 : {
                printf("Enter the ID\n");
                scanf("%d", &id);
                Tree node = findT(t, id);

                if (node == NULL) {
                    printf("No such ID exists!\n");
                } else {
                    printf("Printing student information...\n");
                    printStudent(node->data);
                    printf("\n");

                    printf("Do you want to update their information? enter 1 or 0\n");
                    scanf("%d", &number);

                    if (number) {
                        printf("Enter the new information in the following order : \n"
                               "id, name, address, classID, date (DD/MM/YYYY)\n\n");

                        scanf("%d%s%s%d%s", &id, name, address, &classID, date);
                        Student s1 = {.id= id, .classID = classID};

                        strcpy(s.name, name);
                        strcpy(s.address, address);
                        strcpy(s.date, date);

                        Tree findTree = findT(t, id); //ceh

                        if (node->data.id != id && (findTree == NULL)) {

                            deleteT(t, node->data);
                            insertT(t, s1);

                        } else if (findTree != NULL) {  //checks if a given ID already exists.
                            printf("This ID already exists! you cant add it again.\n\n");
                        } else {
                            node->data = s1;
                        }

                        remove_int(list, id);
                        insertAndSort(list, s1);
                    }

                }
                break;
            }

            //option 3 : print the students information in lexicographic order of their name
            //this is accomplished by repeatedly inserting the students into a list and presort
            // depending on their name as soon as they were added into the main tree, this guarantees that they be
            //sorted in this order without extra overhead.
            case 3 : {
                printList(list);
                break;
            }

            //Option 4 : print all students from a given city in lexigographic order of their names,
            //accomplished much the same as the previous option.
            case 4: {
                int count = 0;

                printf("Enter the city name. \n");
                scanf("%s", address);

                printf("Printing all students from that city...\n]n");
                for (struct node *p = list->next; p != NULL; p = p->next) {

                    if (strcasecmp(address, p->data.address) == 0) {
                        count++;
                        printf("%d : ", count);
                        printStudent(p->data);
                    }
                }

                if (count == 0) {
                    printf("No students from %s\n\n", address);
                }

                break;

            }

            //Option 5 : prints all the students of a given class ID lexigographic order of their names.
            case 5 : {

                int count = 0;

                printf("Enter the class ID\n");
                scanf("%d", &classID);

                printf("Printing all students of class %d...\n\n", classID);
                for (struct node *p = list->next; p != NULL; p = p->next) {

                    if (p->data.classID == classID) {
                        count++;
                        printf("%d : ", count);
                        printStudent(p->data);
                    }
                }

                if (count == 0) {
                    printf("No students in class %d\n\n", classID);
                }

                break;

            }

            //Option 6 : deletes a student given their ID.
            case 6 : {

                printf("Enter the ID of the student to be deleted.\n");
                scanf("%d", &id);
                Tree t1 = findT(t, id);

                if (t1 != NULL) {
                    deleteTid(t, id);
                    remove_int(list, id);
                    printf("student of ID %d has been deleted\n", id);
                }
                else {
                    printf("Student with ID : %d not found!\n", id);
                }

                break;
            }

            //Option 7 : Saves the students information into a file. Basically prints the contents of the list into
            //that file.
            case 7 : {
                p = fopen("students.data", "w");
                printListFile(list, p);
                fclose(p);
                break;
            }

            //Option 8 : exit program
            case 8 :

                printf("Exiting program...");
                exit(0);
            default:
                printf("Please enter a valid number.\n\n");
        }


    }

}

/*
 * Utility function that loads the contents of a file. Takes a list and a pointer to a tree.
 * As well as the file pointer. The output is both the list and the tree that were
 * filled with the contents of the file.
 */
void loadFromFile (FILE *p, struct node *list, Tree *t) {

    int n;
    int id, classID;
    Tree temp = NULL;

    //terminates after reading all the contents of the file.
    while (1) {
        char date[20];
        char name[20];
        char address[20];

        n = fscanf(p, "%d%s%s%d%s", &id, name, address, &classID, date); //reads one line at a time.

        //breaks out when end of file is reached.
        if (n == EOF) {
            break;
        }

        temp = findT(*t, id); //search for the node characterised by a given ID.

        //add the new ID to the tree only if no node has existed before with that ID.
        if (temp == NULL) {
            Student s = {.id = id, .classID = classID}; //create the student with that ID.

            strcpy(s.name, name);
            strcpy(s.address, address);
            strcpy(s.date, date);
            *t = insertT(*t, s); //insert the new node into the tree. Sorted by ID

            insertAndSort(list, s); //insert the student into the list. Sorted by name. repetitions allowed
        }
    }
}

/*
 * Utility function that recursively prints the contents of the tree.
 * In order traversal is used.
 */
void printTree (Tree t) {

    if (t != NULL) {
        printTree(t -> left); //prints the left subtree first. continues function calling untill reaching
                                //the leaf node. Then goes upwards.
        printStudent(t->data);
        printf("\n");
        printTree(t->right);
    }
}

/*
 * Utility Function that searches for a key in a tree. Implemented recursively.
 */
Tree findT (Tree t, int data) {

    //Base case : going beyond the leaf node.

    if (t == NULL) {
        return NULL;
    }
    if (t->data.id == data) {
        return t;
    }
    //search in the left subtree if the needed key is less than the observed data in the node
    else if (t->data.id > data) {
        findT(t->left, data);
    }

    //search in the right subtree if the needed key is more than the observed data in the node
    else {
        findT(t->right, data);
    }
}

/*
 * Utility function that returns the minimum value of the tree.
 */
Tree findMin (Tree t) {

    while (t != NULL) {
        t = t->left;
    }

    return t;
}
/*
 * Utility function that inserts data into the tree. Takes
 * a variable of type student.
 */
Tree insertT (Tree t, Student s) {

    if (t == NULL) {

        Tree x = malloc (sizeof (struct Bnode));
        x->data = s;
        x->left = x->right = NULL;


        return x;
    }

    //insert into the left subtree if the inserted data is less than the
    //value of the node that is being pointed at

    if (t->data.id > s.id) {

        t->left = insertT (t->left, s);
    }

    //insert into the right subtree if the inserted data is more than the
    //value of the node that is being pointed at
    else if (t->data.id < s.id) {
        t->right = insertT (t->right, s);
    }

    //do nothing if a duplicate was inserted
    return t;

}
/*
 * Utility Function that deletes a node given a variable of type student.
 */

Tree deleteT (Tree t, Student s) {
    return deleteTid(t, s.id);
}

/*
 * Utility Function that deletes a node given the ID.
 */

Tree deleteTid (Tree t, int id) {
    if (t == NULL) {
        printf("ID not found.\n");
        return NULL;
    }

    //Search the left subtree if the recieved data is less than the
    //value of the node that is being pointed at
    if (t->data.id > id) {
        t->left = deleteTid(t->left, id);
    }
    //Search the right subtree if the recieved data is more than the
    //value of the node that is being pointed at
    else if (t->data.id < id) {
        t->right = deleteTid (t->right, id);
    }

    else if (t->data.id == id) {
        if (t->left == NULL && t->right == NULL) { //node has 2 children.
            free(t);
            return NULL;
        }
        if (t->right != NULL && t->left == NULL) { //right child.
            Tree temp = t->right;
            free(t);
            return temp;
        }
        if (t->left != NULL && t->right == NULL) { //left child
            Tree temp = t->left;
            free(t);
            return temp;
        }
        else { //leaf node
            t->data = findMin(t)->data;
            t->right = deleteTid (t->right, t->data.id);
        }
    }

    return t; //return the deleted node.
}

/*
 * Utility function that prints the properties of a student.
 */
void printStudent (Student s) {

    printf("ID : %d\n"
           "Name : %s\n"
           "Address : %s\n"
           "Class ID : %d\n"
           "Date : %s\n\n", s.id, s.name, s.address, s.classID, s.date);
}

/*
 * Utility function that inserts a data of type student into a linked list, and presorts
 * depending on the name, and inserts before a duplicated name.
 */

void insertAndSort (struct node* list, Student s) {

    if (isEmpty(list)) { //inserts first if the list is empty
        addFirst(list ,s);
        return;
    }

    struct node *temp = list;

    //increments untill it finds the right position to insert. IE just before
    //the node that has a name with a higher value. So the output is a list
    //sorted in increasing order.

    while ((temp->next != NULL) && (strcasecmp(temp->next->data.name, s.name) < 0)) {
        temp = temp->next;
    }

    //links a node to the pointer that is passed.
    addAfter(list, temp, s);

}

/*
 * Prints the contents of the linked list to a file
 */
void printList(struct node* L) {

    if (isEmpty(L)) {
        printf("The list is empty!\n");
        return;
    }

    for (struct node* p = L->next; p!=NULL;p = p->next) {
        printStudent(p->data);
        printf("\n");
    }
}

/*
 * Prints the properties of a student to a file
 */

void printStudentFile (FILE *p, Student s) {
    fprintf(p, "%d\t%s\t%s\t%d\t%s\t\n", s.id, s.name, s.address, s.classID, s.date);
}

/*
 * Prints the contents of the linked list to a file.
 * Its contents are sorted lexicographically.
 */
void printListFile(struct node* L, FILE *q) {

    if (isEmpty(L)) {
        printf("The list is empty!\n");
        return;
    }

    for (struct node* p = L->next; p!=NULL;p = p->next) {
        printStudentFile(q, p->data);
    }
}

/*
 * This function creates a linked list by first checking if there
 * is some other node that the pointer points to and freeing it if
 * such, and then allocates a memory block for the list, and finally
 * returns a pointer to the head of the list.
 */

struct node* makeEmpty(struct node* L) { //makeEmpty

    if (L != NULL) { //L points to some head node
        deleteList(L);
    }
    L = malloc(sizeof(struct node)); //allocates memory for the new list

    if (L == NULL) { //checks if L is allocated successfully
        printf("out of memory!\n");
        exit(99);
    }

    L -> next = NULL;
    return L;
}

/*
 * Function that takes a head as input and returns
 * whether it is empty or not. The list is empty
 * if and only if the head node points to NULL.
 */

void deleteList(struct node* L) {

    if (L == NULL) {
        return;
    }

    struct node* p;
    p = L -> next;
    L -> next = NULL;
    free(L); //deletes the head

    while (p!=NULL) { //deletes each of the nodes
        struct node* temp = p->next;
        free(p);
        p = temp;
    }
}

/*
 * Function that takes a head as input and returns
 * whether it is empty or not. The list is empty
 * if and only if the head node points to NULL.
 */
int isEmpty(struct node* L) {
    return L->next == NULL;
}


void addFirst (struct node* L, Student data) {

    struct node * newNode = malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Out of memory!");
        exit(99);
    }
    newNode->next = L->next;
    L->next = newNode;
    newNode -> data = data;
}

struct node* findPrevious_int (struct node* L, int id) {

    struct node* p = L;
    int flag = 0;

    while (p -> next != NULL) {
        if (p -> next -> data.id == id) {
            flag = 1;
            break;
        }
        p = p->next;
    }

    return flag? p : NULL;
}

//remove the first occurrence of this letter in the list

void remove_int (struct node* L, int id) {

    struct node* prev = findPrevious_int(L, id);

    if (prev == NULL) {
        printf("Data not found!\n");
        return;
    }
    struct node *temp = prev -> next;
    prev -> next = temp -> next;

    free(temp);
}

/*
 * Adds a node after the pointer that is passed.
 */

void addAfter (struct node *list, struct node* ptr, Student data) {

    struct node *p = malloc(sizeof(struct node));

    if (p == NULL) {
        printf("Out of memory!");

    }
    p->data = data;
    p->next = ptr->next;
    ptr->next = p;
}
