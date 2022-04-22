public class BankerAlgorithm {
    private  int numberOfProcesses;
    private int numberOfResources;
    private  int [] initialAvailable; // initial number of resources that are available
    private int [] currentAvailable; //the currentAvailable amount of each resource
   private int [][] maximum; //the maximum demand of each process
   private int [][] allocation; // the allocated resources of each process
    private int [][] need; // the remaining needed resources for each process
    private boolean [] finishedProcesses;
    private  boolean safeState;
    public BankerAlgorithm(int number_of_processes ,int number_of_resources) {
        numberOfProcesses = number_of_processes;
        numberOfResources = number_of_resources;

        currentAvailable = new int[numberOfResources];
        allocation = new int[numberOfProcesses][numberOfResources];
        maximum = new int[numberOfProcesses][numberOfResources];
        need = new int[numberOfProcesses][numberOfResources];
        finishedProcesses = new boolean[numberOfProcesses];
        assignFinish(); // assign all processes to flase
        safeState = false; // set the  current state of the system to be unsafe  before check for safety
    }

    public void setInitialAvailable(int[] initialAvailable) {
        this.initialAvailable = initialAvailable;
    }
    // calculate the current number of available instance of each resource
    public void calcCurrentAvailable()
    {
        for(int i = 0; i < numberOfResources; ++i)
        {
            int sum = 0;
            for(int j = 0; j < numberOfProcesses; ++j)
            {
                sum += allocation[j][i];
            }
            currentAvailable[i] = initialAvailable[i] - sum;
        }
    }
    public void setMaximum(int[][] maximum) {
        this.maximum = maximum;
    }
    public void setAllocation(int[][] allocation) {
        this.allocation = allocation;
        calcNeed();  // calculate need matrix
        calcCurrentAvailable();  // calculate current available vector of resources
    }
    public void assignFinish()
    {
        for(int i = 0; i < numberOfProcesses; ++i)
        {
            finishedProcesses[i] = false;
        }
    }
    // calculate the need matrix
    public void calcNeed() {
        for(int i = 0; i < numberOfProcesses; ++i)
        {
            for(int j = 0; j < numberOfResources; ++j)
            {
                need[i][j] = maximum[i][j] - allocation[i][j];
            }
        }
    }

    public void printCurrentAvailable()
    {
        for(int j = 0; j < numberOfResources; ++j)
        {
            System.out.print(currentAvailable[j]+" ");
        }
    }

    // print the current state of the system and check if the system is safe or unsafe
    public void printCurrentState()
    {
       // printResources();
        System.out.println("    Allocation      Maximum     Need        Available");
        boolean flag = false;
        for(int i = 0; i < numberOfProcesses; ++i)
        {
            System.out.print("P"+i+"  ");
            for(int j = 0; j < numberOfResources; ++j)
            {
                System.out.print(allocation[i][j]+" ");
            }
            System.out.print("          ");
            for(int j = 0; j < numberOfResources; ++j)
            {
                System.out.print(maximum[i][j]+" ");
            }
            System.out.print("      ");
            for(int j = 0; j < numberOfResources; ++j)
            {
                System.out.print(need[i][j]+" ");
            }
            System.out.print("      ");
            // print currentAvailable only one time
            if(!flag)
            {
                printCurrentAvailable();
                flag = true;
            }
            System.out.println("\n");
        }
    }
    // check if all processes have finished
    boolean allFinished()
    {
        for(int i = 0; i < numberOfProcesses; ++i)
        {
            if(!finishedProcesses[i])
            {
                return false;
            }
        }
        return  true;
    }
    // update allocation matrix after request
    public void addRequestToAllocation(int[] request, int processNumber)
    {
        for(int i = 0; i < numberOfResources; ++i)
        {
            allocation[processNumber][i] += request[i];
        }
        calcNeed();
        calcCurrentAvailable();
    }

    // check if request can be granted
    public void verifyRequest(int[] request, int processNumber)
    {
        calcCurrentAvailable();
        // if need is less than request or currentAvailable less than request so request is invalid from the beginning
        for(int i = 0; i < numberOfResources; ++i)
        {
            if(currentAvailable[i] < request[i] || need[processNumber][i] < request[i])
            {
                System.out.println("Invalid Request");
                return;
            }
        }
        addRequestToAllocation(request,processNumber); // update allocation matrix
        calcCurrentAvailable(); // update current available vector of resources
        checkSafeState(); // check if system is safe or unsafe after that request

        if(safeState) // if system in safe state after request is added
        {
            System.out.println("Valid Request");
        }
        else
        {
            System.out.println("Invalid Request");
        }

        // after request has been verified return the system to the previous state to check for another request
        for(int i = 0; i < numberOfResources; ++i)
        {
            allocation[processNumber][i] -= request[i];
        }
        calcCurrentAvailable(); //update current available vector
        calcNeed(); // update need matrix

    }

    // check if a process can release some of it's allocated resources
    public void verifyRelease(int[]release, int processNumber)
    {
        for(int i = 0; i < numberOfResources; ++i)
        {
            if(allocation[processNumber][i] <  release[i])
            {
                System.out.println("Invalid release");
                return;
            }
        }

        for(int i = 0; i < numberOfResources; ++i)
        {
            allocation[processNumber][i] -= release[i];
        }
        calcCurrentAvailable();
        calcNeed();

        System.out.println("Valid release");
        printCurrentState();

        // return system to previous state
        for(int i = 0; i < numberOfResources; ++i)
        {
            allocation[processNumber][i] += release[i];
        }
        calcCurrentAvailable();
        calcNeed();
        printCurrentState();
    }
    // check if system in safe state
    public void checkSafeState()
    {

        String SafeStateSequence ="";
        int count = 0;
        int notGrantedProcesses = numberOfProcesses;
        assignFinish(); // set all finish process to be false
        printCurrentState(); // print the current state of the system
        safeState = false; // assign safe state to false every time we check for safe state
        // loop until check all processes
        while(count != notGrantedProcesses)
        {
            for(int i = 0; i < numberOfProcesses; ++i)
            {
                boolean foundProcess = true;
                int matchedProcess = i;
                if(finishedProcesses[i]) continue;

               for(int j = 0; j < numberOfResources; ++j)
               {

                        if(need[i][j] >  currentAvailable[j])
                        {
                            foundProcess = false;
                            System.out.println("P"+ i + " need can't be granted at that time");
                            printCurrentState();
                            count++;
                            break;

                        }

               }

               // process that not finish and can grant needed
               if(foundProcess)
               {
                   finishedProcesses[matchedProcess] = true;
                   for(int j = 0; j < numberOfResources; ++j)
                   {
                       // update currentAvailable
                       currentAvailable[j] += allocation[matchedProcess][j];

                   }
                  notGrantedProcesses--;
                   count = 0;
                   System.out.println("P" + i + " need is granted");
                   // add process to Safe state sequence
                  SafeStateSequence += "P" + matchedProcess + "->";
                   printCurrentState();

               }

            }

        }

        if(!allFinished())
        {
            System.out.println("System in Unsafe State");

        }
        else {

            System.out.println("Safe State Sequence: " + SafeStateSequence);
            System.out.println("System in Safe State");
            safeState = true;
        }
    }
    // to recover from the deadlock if system is in unsafe state
    public void recover()
    {
      for(int i = 0; i < numberOfProcesses; ++i)
      {
          for(int j = 0; j < numberOfResources; ++j)
          {
              allocation[i][j] = 0;
          }
          System.out.println("Selecting P"+i+" as victim now check for deadlock");
          calcCurrentAvailable();
          calcNeed();
          checkSafeState();
          if(safeState )
          {
              System.out.println("Successfully recover form deadlock");
              break;
          }

      }
    }
}

