=======
TODO:
=======

In list.h and list.c:
=====================

* add functions like joining, splitting and copying

* use LIST_FOREACH to implement List_remove()

In list_algos.c:
================

* optimize List_bubble_sort() according to Wiki pages http://en.wikipedia.org/wiki/Bubble_sort

* optimize List_merge_sort()

    + make use of List_split and List_join 
    + reduce the amount of copying and creating lists
    + implement the "bottom up" merge sort
   
* implement List_insert_sort()    

In list_algos_tests.c:
======================

* Find a way to simulate filling different sized random lists and measuring how long each sort algorithm takes





