import java.util.Scanner;

public class Main {

    public static  void  main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int numOfProcesses , numOfResources, processNumber ;
        int [] InitialavailableResources;
        int [][] allocationResource;
        int [][] maximumNeedResources;
        int [] request;
        int [] release;

        System.out.print("Enter the number of Processes: ");
        numOfProcesses = input.nextInt();
        System.out.print("Enter the number of Resources: ");
        numOfResources = input.nextInt();


        InitialavailableResources = new int[numOfResources];
        allocationResource = new int[numOfProcesses][numOfResources];
        maximumNeedResources = new int[numOfProcesses][numOfResources];
        request = new int[numOfResources];
        release = new int[numOfResources];

        System.out.print("Enter the available number of each resource\n");

        for(int i = 0; i < numOfResources; ++i)
        {
            InitialavailableResources[i] = input.nextInt();
        }

        System.out.print("Enter the Maximum number of  resources for each process\n");

        for(int i = 0; i < numOfProcesses; ++i)
        {
            for(int j = 0; j < numOfResources; ++j)
            {
                maximumNeedResources[i][j] = input.nextInt();
            }
        }

        System.out.print("Enter the Allocation number of  resources for each process\n");

        for(int i = 0; i < numOfProcesses; ++i)
        {
            for(int j = 0; j < numOfResources; ++j)
            {
                allocationResource[i][j] = input.nextInt();
            }
        }

        BankerAlgorithm bn = new BankerAlgorithm(numOfProcesses,numOfResources);
        bn.setInitialAvailable(InitialavailableResources);
        bn.setMaximum(maximumNeedResources);
        bn.setAllocation(allocationResource);




        bn.checkSafeState();

        String choice;



        while(true)
        {
            System.out.print("Enter (RQ) or (RL) or (Recover) or (Quit)\n");

            choice = input.next();

            // check if a process can request another resources
            if(choice.equalsIgnoreCase("rq"))
            {
                System.out.print("Enter Process number: ");
                processNumber = input.nextInt();
                System.out.println();
                System.out.print("Enter the request\n");
                for(int i = 0; i < numOfResources; ++i){
                    System.out.print("Resource" + i +": ");
                    request[i] = input.nextInt();
                }
                bn.verifyRequest(request,processNumber);
            }

            // release some allocation resources from a process
            else if(choice.equalsIgnoreCase("rl"))
            {
                System.out.print("Enter Process number: ");
                processNumber = input.nextInt();
                System.out.print("Enter the release for each resource\n");
                for(int i = 0; i < numOfResources; ++i){
                    System.out.print("Resource" + i +": ");
                    release[i] = input.nextInt();
                }
                bn.verifyRelease(release,processNumber);
            }
            // recover from the deadlock if deadlock is found
            else if(choice.equalsIgnoreCase("recover"))
            {
                bn.recover();
            }
            else {
                break;
            }
        }
    }
}
