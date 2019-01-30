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
  

  for (int run = 0; run < n_runs; ++run)
  {
    int this_run_start = start + run * run_size;

    cout << "preparing for run " << run + 1 << endl;
    vector<bool> sieve(run_size, true);

    prepare_sieve(run, this_run_start, run_size, primes, sieve);
    cout << "looping\n";
    while (true)
    {
      bool tested_to_end_of_sieve = run_sieve(this_run_start, run_size, primes, sieve);
      if (tested_to_end_of_sieve)
      {
        break;
      }
    }
    print(primes);
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

bool prune_sieve(myint_t start, myint_t run_size, myint_t prime, vector<bool> & sieve)
{
  cout << "pruning from " << start << " with " << prime << endl;
  
  myint_t first_index;

  if (prime > start)
  {
    first_index = prime;
  }
  else
  {
    first_index = (start % prime);
    if (first_index != 0)
    {
      first_index = start - first_index;
    }
  }

  cout << "first index " << first_index << endl;

  if (first_index >= run_size)
  {
    cout << "too big, returning" << endl;
    return false;
  }

  print(sieve);
  for (myint_t x = first_index; x < run_size; x += prime)
  {
    sieve[x] = false;
  }
  print(sieve);
  return true;
}

void prepare_sieve(int run, myint_t start, myint_t run_size, vector<myint_t> & primes, vector<bool> & sieve)
{
  if (run == 0)
  {
    sieve[0] = false;
    sieve[1] = false;
  }
  else
  {
    for (myint_t prime_index = 0; prime_index < primes.size(); ++ prime_index)
    {
      if (!prune_sieve(start, run_size, primes[prime_index], sieve))
      {
        // prune sieve returns false once the end of the batch of numbers is passed, so stop checking
        break;
      }
    }
  }
}

bool run_sieve(myint_t start, myint_t run_size, vector<myint_t> & primes, vector<bool> & sieve)
{
  myint_t latest_prime = primes.back();

  cout << "latest " << latest_prime << endl;

  if (!prune_sieve(start, run_size, latest_prime, sieve)) return true;

  myint_t prime_test_index = (latest_prime > start) ? latest_prime - start : (run_size % latest_prime);

  cout << "start:     " << start << endl;
  cout << "run size:  " << start << endl;
  cout << "latest:    " << latest_prime << endl;
  cout << "first pti: " << prime_test_index << endl;
  cout << "run size:  " << run_size << endl;


  for (prime_test_index  ; prime_test_index < run_size; ++prime_test_index)
  {
    cout << "testing index " << prime_test_index << " " << start + prime_test_index << " " << (sieve[prime_test_index] ? "true" : "false") << endl;
    if (sieve[prime_test_index])
    {
      primes.push_back(start + prime_test_index);
      break;
    }
  }
  //print(primes);
  return (prime_test_index == run_size);
}
