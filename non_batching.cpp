#include <vector>
#include <iostream>
#include <cstdlib>

using std::vector;
using std::cout;
using std::endl;

typedef uint64_t myint_t;


bool run_sieve(myint_t start, myint_t run_size, vector<myint_t> & primes, vector<bool> & sieve);
void prepare_sieve(int run, myint_t start, myint_t run_size, vector<myint_t> & primes, vector<bool> & sieve);
void print(vector<bool> & sieve);
void print(vector<myint_t> & primes);

int main(int argc, char *argv[])
{
  myint_t start = 0;
  myint_t run_size = atoi(argv[1]);
  myint_t n_runs = (argc > 2 ? atoi(argv[2]) : 1);
  int run = 0;
  vector<myint_t> primes(1,2);
  vector<bool> sieve;

  for (int run = 0; run < n_runs; ++run)
  {

    cout << "preparing for run " << run + 1 << endl;
   
    prepare_sieve(run, start, run_size, primes, sieve);
    cout << "looping\n";
    while (true)
    {
      bool tested_to_end_of_sieve = run_sieve(start + run * run_size, run_size, primes, sieve);
      if (tested_to_end_of_sieve)
      {
        break;
      }
    }
    //print(primes);
    cout << primes.size() << " primes up to " << run_size * (run + 1) << " (non incluseive).\n\n";
  }
  
    
  return 0;
}

void print(vector<bool> & sieve)
{
  for (myint_t x = 0; x < sieve.size(); ++x)
  {
    cout << x << ": " << sieve[x] << ", ";
  }
  cout << endl; 
}

void print(vector<myint_t> & primes)
{
 for (myint_t x = 0; x < primes.size(); ++x)
  {
    cout << primes[x] << ", ";
  }
  cout << endl;
}

void prune_sieve(myint_t start, myint_t run_size, myint_t prime, vector<bool> & sieve)
{
  myint_t first_index = start + (prime % run_size);
  for (myint_t x = first_index; x < run_size; x += prime)
  {
    sieve[x] = false;
  }
}

void prepare_sieve(int run, myint_t start, myint_t run_size, vector<myint_t> & primes, vector<bool> & sieve)
{
  sieve = vector<bool>(run_size, true);

  if (run == 0)
  {
    sieve[0] = false;
    sieve[1] = false;
  }
  else
  {
    for (myint_t prime_index = 0; prime_index < primes.size(); ++ prime_index)
    {
      prune_sieve(start, run_size, primes[prime_index], sieve);
    }
  }
  //print(sieve);
}

bool run_sieve(myint_t start, myint_t run_size, vector<myint_t> & primes, vector<bool> & sieve)
{
  myint_t latest_prime = primes.back();

  // cout << "latest " << latest_prime << endl;

  prune_sieve(start, run_size, latest_prime, sieve);


  myint_t prime_test_index;

  // cout << "start:     " << start << endl;
  // cout << "latest:    " << latest_prime << endl;
  // cout << "first pti: " << latest_prime % run_size  << endl;
  // cout << "run size:  " << run_size << endl;


  for (prime_test_index = latest_prime ; prime_test_index < run_size; ++prime_test_index)
  {
    //cout << "pti " << prime_test_index << endl;
    if (sieve[prime_test_index])
    {
      primes.push_back(start + prime_test_index);
      break;
    }
  }
  //print(primes);
  return (prime_test_index == run_size);
}
