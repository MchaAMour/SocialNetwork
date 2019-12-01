/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <algorithm>
#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <list>







class User
{
public:



  User (std::string name,
	unsigned int age = 0,
	unsigned int height = 0, std::vector < std::string > hobbies =
	{
	"\0"}, std::vector < std::string > frndsNames =
	{
"\0"}, int ID = 0):

  name_ (name),
    age_ (age),
    height_ (height), hobbies_ (hobbies), frndsNames_ (frndsNames), ID_ (ID)
  {
    std::cout << "\n" << "i am in the constructor" << std::endl;
  }
  ~User ()
  {
    std::cout << "i am in the deconstructor" << std::endl;
  }




  std::string GetName (void) const
  {
    return name_;
  }
  unsigned int GetAge (void) const
  {
    return age_;
  }
  unsigned int GetHeight (void) const
  {
    return height_;
  }
  int GetID (void) const
  {
    return ID_;
  }
  const std::vector < std::string > &GetHobbies (void) const
  {
    return hobbies_;
  }
  const std::vector < std::string > &GetFriends (void) const
  {
    return frndsNames_;
  }


private:
    std::string name_;
  unsigned int age_, height_;
  std::vector < unsigned int >friends_;
  std::vector < std::string > hobbies_;
  std::vector < std::string > frndsNames_;
  int ID_;

};


class SocialNetwork
{
public:
  void AddUser (std::string name,
		unsigned int age,
		unsigned int height,
		std::vector < std::string > hobbies,
		std::vector < std::string > frndsNames);

  void PrintUser (std::shared_ptr < User > P);
  void SearchAge (unsigned int age);
    std::shared_ptr < User > SearchId (int Id);
    std::vector < std::shared_ptr < User >> SearchName (std::string name);
  void GetFriends (int id);
    std::list < std::shared_ptr < User >> SearchHobbies (std::list <
							 std::string > hobby);


private:
    std::unordered_multimap < std::string, std::shared_ptr < User > >NameMap;
    std::unordered_multimap < unsigned int, std::shared_ptr < User > >AgeMap;
    std::unordered_map < int, std::shared_ptr < User > >IdMap;
    std::unordered_multimap < std::string,
    std::list < std::shared_ptr < User >> >HobbiesMap;


};

std::list < std::shared_ptr <
  User >> SocialNetwork::SearchHobbies (std::list < std::string > hobbies)
{
  std::list < std::shared_ptr < User > >RetVal;
  std::list < std::shared_ptr < User > >UniqueList;
for (const auto & hobbie:hobbies)
    {
      auto it = HobbiesMap.find (hobbie);

    for (const auto & ptr:it->second)
	{
	  UniqueList.push_back (ptr);
	}

    }
  std::list < std::shared_ptr < User >> OccurenceList (UniqueList);
  UniqueList.sort ();
  UniqueList.unique ();
for (const auto & ptr:UniqueList)
    {
      if (std::count (OccurenceList.begin (), OccurenceList.end (), ptr) ==
	  hobbies.size ())
	{
	  std::cout << "****************************************************"
	    << std::endl;
	  PrintUser (ptr);
	  RetVal.push_back (ptr);
	  std::cout << "****************************************************"
	    << std::endl;
	}
    }

  return RetVal;
}

void
SocialNetwork::AddUser (std::string name,
			unsigned int age = 0,
			unsigned int height = 0,
			std::vector < std::string > hobbies =
			{
			"\0"}, std::vector < std::string > frndsNames =

			{
			"\0"})

{
  int ID = rand ();

  std::shared_ptr < User > Ptr =
    std::make_shared < User > (name, age, height, hobbies, frndsNames, ID);
  IdMap.insert (std::make_pair (ID, Ptr));
  AgeMap.insert (std::make_pair (age, Ptr));
  NameMap.insert (std::make_pair (name, Ptr));
  std::weak_ptr < User > Pwk = Ptr;
for (auto f:frndsNames)
    {


    }




for (const auto & hobbie:hobbies)
    {
      auto it = HobbiesMap.find (hobbie);

      if (it != HobbiesMap.end ())
	{
	  it->second.push_back (Ptr);
	}
      else
	{
	  std::list < std::shared_ptr < User > >NewList;
	  NewList.push_back (Ptr);
	  HobbiesMap.insert (std::make_pair (hobbie, NewList));
	}

    }






}

void
SocialNetwork::PrintUser (std::shared_ptr < User > P)
{


  std::cout << "Name is " << P->
    GetName () << "\n" << "Age is " << P->GetAge () << "\n" << "height is " <<
    P->GetHeight () << "\n" << "ID is " << P->GetID () << "\n" << std::endl;
  std::cout << "Users hobbies are " << std::endl;
for (auto i:P->GetHobbies)
    {
      std::cout << P->GetAge << " likes " << i << std::endl;
    }
  std::cout << "Users friends IDs are " << std::endl;
for (auto i:(P->GetFriends))
    {
      std::cout << " 'ID is  " << P->GetFriends << i << std::endl;
    }




}

void
SocialNetwork::GetFriends (int id)
{
  std::vector < std::shared_ptr < User >> x;
  std::vector < std::string > list;
  std::shared_ptr < User > P;
  P = SearchId (id);
for (auto & i:P->GetFriends ())
    {
      list.push_back (i);
    }

  for (auto &j : list) {std::cout <<"Here" <<j << std::endl;}

std::vector < std::shared_ptr <
  User >> SocialNetwork::SearchName (std::string name)
{
  std::vector < std::shared_ptr < User >> P;
  auto range = NameMap.equal_range (name);
  for (auto it = range.first; it != range.second; ++it)
    {
      P.push_back (it->second);
    }

  return P;
}


void
SocialNetwork::SearchAge (unsigned int age)
{

  auto range = AgeMap.equal_range (age);
  for (auto it = range.first; it != range.second; ++it)
    {
      PrintUser (it->second);
    }

}

std::shared_ptr < User > SocialNetwork::SearchId (int Id)
{
  auto it = IdMap.find (Id);
  if (it != IdMap.end ())
    {
      return (it->second);
    }
  else
    {
      return 0;
    }
}







int
main ()
{


  SocialNetwork SN;

  SN.AddUser ("mcha", 29, 177,
	      {
	      "tennis", "basket", "running"},
	      {
	      "omar", "hamo", "hoda", "banna"});
  SN.AddUser ("omar", 28, 188,
	      {
	      "tennis", "basket", "soccer"},
	      {
	      "omar", "hamo", "hoda", "banna"});
  SN.AddUser ("omar", 27, 190,
	      {
	      "skating", "swimming", "rugby"},
	      {
	      "omar", "hamo", "hoda", "banna"});
  SN.AddUser ("mai", 29, 173,
	      {
	      "volin", "voice_over", "dancing"},
	      {
	      "toqa", "ola", "amany", "omnya"});
  SN.AddUser ("wezza", 23, 190,
	      {
	      "netflix", "basket", "tennis"},
	      {
	      "Khairy", "mcha"});

  std::list < std::string > hob
  {
  "tennis", "basket"};
  std::list < std::shared_ptr < User >> allhob = SN.SearchHobbies (hob);
  //std::vector<std::shared_ptr<User>> P;
  //P = SN.SearchName("omar");
  //for (auto i: P) {
  // SN.PrintUser(i); 
  //}
  //
  //SN.SearchId(19169);
  //SN.SearchAge(29);
  //SN.SearchName("mcha");
  //SN.GetFriends(41);
  //SN.SearchAge(29);


  return 0;
}
