struct Point
{
        int x;
        int y;
};

class Stack
{
public:
   struct node
      {
         node(){point.x = -1; point.y = -1; next = NULL;}
         Point point;
         node *next;
      };
   Stack(){head = NULL;}
  // ~Stack(){while(head) pop();}
   bool empty(){return (head) ? 0:1;}
   bool push(int x, int y)
      {
         node *new_data = new node;
         new_data->point.x = x;
         new_data->point.y = y;
         new_data->next = head;
         head = new_data;
      return 0;
      }

   Point pop()
      {
         Point cash;
         node *del;
         cash = head->point;
         del = head;
         head = head->next;
delete del;
      return cash;
      }

   bool print()
      {
         if(empty()) return 1;
         node *curr = head;
         while (curr)
            {
               cout << curr->point.x << " " << curr->point.y << endl;
               curr = curr->next;
            }
      return 0;
      }
private:
   node *head;
};
