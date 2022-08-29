#ifndef LINKED_MATRIX_H
#define LINKED_MATRIX_H

#include <vector>

using namespace std;

class Column;

class Node {
  int _row_id;
  Column *_column;
  Node *_right;
  Node *_left;
  Node *_up;
  Node *_down;

public:
  Node(int row_id = -1, Column *column = NULL, Node *right = NULL,
       Node *left = NULL, Node *up = NULL, Node *down = NULL)
      : _row_id(row_id), _column(column), _right(right), _left(left), _up(up),
        _down(down) {}

  void set_row_id(int id) { _row_id = id; }
  int row_id() { return _row_id; }
  void set_column(Column *column) { _column = column; }
  Column *column() const { return _column; }
  Node *right() const { return _right; }
  Node *left() const { return _left; }
  Node *up() const { return _up; }
  Node *down() const { return _down; }
  void set_right(Node *right) { _right = right; }
  void set_left(Node *left) { _left = left; }
  void set_up(Node *up) { _up = up; }
  void set_down(Node *down) { _down = down; }
};

class Column : public Node {
  int _size;

public:
  Column(int size = 0) : Node(-1, this), _size(size) {}

  int size() const { return _size; }
  void set_size(int size) { _size = size; }
  void add_to_size(int n) { _size += n; }
};

class Matrix {
  Node *_root;

public:
  Matrix();
  Matrix(const vector<vector<bool>> &matrix, int m, int n);
  Node *head() const;

  bool is_empty() const;
  int number_of_rows() const;
  void remove_row(Node *node);
  void restore_row(Node *node);
  void remove_column(Node *node);
  void restore_column(Node *node);

  ~Matrix();
};

#endif
