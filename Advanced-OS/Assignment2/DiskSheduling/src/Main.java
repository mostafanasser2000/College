import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args)
    {
        int headStart,rqSize, diskSize;
        Scanner input = new Scanner(System.in);
        System.out.print("Please Enter the start head: ");
        headStart = input.nextInt();
        System.out.print("Please Enter the total number of disk cylinders: ");
        diskSize = input.nextInt();
        System.out.print("Please Enter the request Size: ");
        rqSize = input.nextInt();
        ArrayList<Integer> requestQueue = new ArrayList<>();
        for(int i = 0; i < rqSize; ++i)
        {
            int request = input.nextInt();
            requestQueue.add(request);
        }
        DiskSchedulingAlgorithms schedulingAlgorithmSelector = new DiskSchedulingAlgorithms(requestQueue,headStart,diskSize);
        System.out.println("Please choose one of the following");
        System.out.println("1- First Come First Served (FCFS)\n" +
                "2- Shortest Seek Time First (SSTF)\n" +
                "3- Scan\n" +
                "4- C-Scan\n" +
                "5- Look\n" +
                "6- C-Look\n");
        int choice = input.nextInt();
        switch (choice)
        {
            case 1:
            {
                schedulingAlgorithmSelector.FSFC();
                break;
            }
            case 2: {
                schedulingAlgorithmSelector.SSTF();
                break;
            }
            case 3:{
                schedulingAlgorithmSelector.SCAN();
                break;
            }
            case 4:{
                schedulingAlgorithmSelector.C_SCAN();
                break;
            }
            case 5:{
                schedulingAlgorithmSelector.LOOK();
                break;
            }
            case 6:{
                schedulingAlgorithmSelector.C_LOOK();
                break;
            }
            default:{
                System.out.println("Invalid Choice");
            }
        }
    }
}
