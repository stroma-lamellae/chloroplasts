#include "PoolQueue.h"
#include "SillyString.h"

//Print menu.
void printMenu(){
  std::cout<<"1. Add One\t\t2. Add Two\t\t3. Add Three\t\t4.Add Four\n";
  std::cout<<"5. Remove One\t\t6. Remove Two\t\t7. Remove Three\t\t8.Remove Four\n";
  std::cout<<"\t\t\t9. Test Options\t\t0. Quit\n";
}

int main(){
  PoolQueue::PoolQueue<SillyString::SillyString> s;
  SillyString::SillyString aa;
  SillyString::SillyString bb;
  SillyString::SillyString cc;
  SillyString::SillyString dd;
  std::vector<int> yo_da;
  std::string w_name;
  int choice= -1;
  while(choice != 0){
    printMenu();
    std::cin>>choice;
    switch (choice) {
        //Add One
        case 1:
            std::cout << "First name: ";
            std::cin >> w_name;
            w_name = w_name;
            aa = SillyString::SillyString(w_name.c_str());
            s.addSingle(aa);
            break;
        //Add two
        case 2:
            std::cout << "First name: ";
            std::cin >> w_name;
            aa = SillyString::SillyString(w_name.c_str());
            std::cout << "Second name: ";
            std::cin >> w_name;
            bb = SillyString::SillyString(w_name.c_str());
            s.addPair(aa, bb);
            break;
        //Add three
        case 3:
            std::cout << "First name: ";
            std::cin >> w_name;
            aa = SillyString::SillyString(w_name.c_str());
            std::cout << "Second name: ";
            std::cin >> w_name;
            bb = SillyString::SillyString(w_name.c_str());
            std::cout << "Third name: ";
            std::cin >> w_name;
            cc = SillyString::SillyString(w_name.c_str());
            s.addTriplet(aa, bb, cc);
            break;
        //Add four
        case 4:
            std::cout << "First name: ";
            std::cin >> w_name;
            aa = SillyString::SillyString(w_name.c_str());
            std::cout << "Second name: ";
            std::cin >> w_name;
            bb = SillyString::SillyString(w_name.c_str());
            std::cout << "Third name: ";
            std::cin >> w_name;
            cc = SillyString::SillyString(w_name.c_str());
            std::cout << "Fourth name: ";
            std::cin >> w_name;
            dd = SillyString::SillyString(w_name.c_str());
            s.addQuartet(aa, bb, cc, dd);
            break;
        //Add remove one
        case 5:
            s.removeSingle(0,s.count());
            break;
        //Add remove two
        case 6:
            s.removePair(0,s.count());
            break;
        //Add remove three
        case 7:
            s.removeTriplet(0,s.count());
            break;
        //Add remove four
        case 8:
            s.removeQuartet(0,s.count());
            break;
        //Check if groups exist
        case 9:
            s.hasSingle();
            s.hasPair();
            s.hasTriplet();
            s.hasQuartet();
            std::cout<<"Count:"<<s.count()<<std::endl;
            break;
          }

        }
}
