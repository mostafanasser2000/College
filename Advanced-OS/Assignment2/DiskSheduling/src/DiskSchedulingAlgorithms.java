import java.util.ArrayList;
import java.util.Collections;

public class DiskSchedulingAlgorithms {
    private ArrayList<Integer> sectorsRequests;
    private int currentRequest;
    private int seekTime;
    private final int endCylinder;
    public DiskSchedulingAlgorithms(ArrayList<Integer> request, int startHead,int endCylinder)
    {
        currentRequest = startHead;
        sectorsRequests = request;
        this.endCylinder = endCylinder;
    }

    // First Come First Served Algorithm
    public void FSFC()
    {
         seekTime = 0;
         System.out.println("Order");
        for (int nextRq : sectorsRequests) {
            seekTime += Math.abs(currentRequest - nextRq);
            System.out.print("(" + currentRequest + "-->" + currentRequest + "), ");
            currentRequest = nextRq;
        }
        System.out.println();
       printSeekTime(seekTime);
    }
    // Shortest Seek Time First
    public void SSTF(){
        seekTime = 0;
        System.out.println("Order");

        while(sectorsRequests.size() > 0)
        {
            int short_distance = 100000;
            int nextRq = 0;
            // search for the request that had the shortest distance form the current currentRequest
            for (int curr : sectorsRequests) {
                if (short_distance > Math.abs(currentRequest - curr)) {
                    short_distance = Math.abs(currentRequest - curr);
                    nextRq = curr;
                }
            }
            
            System.out.print("(" + currentRequest +"-->" + currentRequest+"), ");
            currentRequest = nextRq;
            seekTime += short_distance;
            
            // remove the request after it has been served
            sectorsRequests.remove(sectorsRequests.indexOf(nextRq));
        }
        System.out.println();
        printSeekTime(seekTime);

    }
    // C-SCAN Algorithm
    public void C_SCAN()
    {
        seekTime = 0;
        System.out.println("Order");
        sectorsRequests.add(0);
        sectorsRequests.add(currentRequest);
        sectorsRequests.add(endCylinder);
        Collections.sort(sectorsRequests);
        int requestQueueSize = sectorsRequests.size();
        int startHeadPosition = sectorsRequests.indexOf(currentRequest);
        int currentHeadPosition = startHeadPosition;

        while(true)
        {
            int nextHeadPosition = (currentHeadPosition + 1) % requestQueueSize;

            // if we reach to the start position of the arm head then we finish
            if(nextHeadPosition == startHeadPosition)
            {
                break;
            }
            currentRequest = sectorsRequests.get(currentHeadPosition);
            int nextRequest = sectorsRequests.get(nextHeadPosition);
            seekTime += Math.abs(nextRequest - currentRequest);
            currentHeadPosition = nextHeadPosition;
            System.out.print("(" + currentRequest +"-->" + nextRequest+"), ");
        }
        System.out.println();
        printSeekTime(seekTime);
    }
    //SCAN Algorithm
    public void SCAN()
    {
         sectorsRequests.add(currentRequest);
         sectorsRequests.add(endCylinder);
         Collections.sort(sectorsRequests);
         int startHeadPosition = sectorsRequests.indexOf(currentRequest);

         boolean []finish = new boolean[100000];
         System.out.println("Order");
         for(int i = startHeadPosition+1; i < sectorsRequests.size(); ++i)
         {

             int nextRequest = sectorsRequests.get(i);
             System.out.print("(" + currentRequest +"-->" + nextRequest+"), ");
             seekTime += Math.abs(currentRequest - nextRequest);
             currentRequest = nextRequest;
         }
         int requestQueueSize = sectorsRequests.size();

         for(int i = requestQueueSize-2; i >=0; --i)
         {
             int nextRequest = sectorsRequests.get(i);
             if(!finish[nextRequest])
             {
                 System.out.print("(" + currentRequest +"-->" + nextRequest+"), ");
                 seekTime += Math.abs(currentRequest - nextRequest);
                 currentRequest = nextRequest;
                 finish[currentRequest] = true;
             }
         }
         System.out.println();
         printSeekTime(seekTime);
    }

    // LOOK Algorithm
    public void LOOK()
    {
        sectorsRequests.add(currentRequest);
        Collections.sort(sectorsRequests);
        int startHeadPosition = sectorsRequests.indexOf(currentRequest) ;
        boolean []finish = new boolean[100000];
        System.out.println("Order");
        for(int i = startHeadPosition+1; i < sectorsRequests.size(); ++i)
        {
            finish[currentRequest] = true;
            int nextRequest = sectorsRequests.get(i);
            System.out.print("(" + currentRequest +"-->" + nextRequest+"), ");
            seekTime += Math.abs(currentRequest - nextRequest);
            currentRequest = nextRequest;
        }
        int requestQueueSize = sectorsRequests.size();
        for(int i = requestQueueSize-2; i >=0; --i)
        {
            int nextRequest = sectorsRequests.get(i);
            if(!finish[nextRequest])
            {
                System.out.print("(" + currentRequest +"-->" + nextRequest+"), ");
                seekTime += Math.abs(currentRequest - nextRequest);
                currentRequest = nextRequest;
                finish[currentRequest] = true;
            }
        }
        System.out.println();
        printSeekTime(seekTime);
    }

    // C-LOOK Algorithm
    public void C_LOOK()
    {
        seekTime = 0;
        System.out.println("Order");
        sectorsRequests.add(currentRequest);
        Collections.sort(sectorsRequests);
        int requestQueueSize = sectorsRequests.size();
        int startHeadPosition = sectorsRequests.indexOf(currentRequest);
        int currentHeadPosition = startHeadPosition;

        while(true)
        {
            int nextHeadPosition = (currentHeadPosition + 1) % requestQueueSize;
            if(nextHeadPosition == startHeadPosition)
            {
                break;
            }
            currentRequest = sectorsRequests.get(currentHeadPosition);
            int nextRequest = sectorsRequests.get(nextHeadPosition);
            seekTime += Math.abs(nextRequest - currentRequest);
            currentHeadPosition = nextHeadPosition;
            System.out.print("(" + currentRequest +"-->" + nextRequest+"), ");
        }
        System.out.println();
        printSeekTime(seekTime);
    }
    public void printSeekTime(int cylinders)
    {
        System.out.println("Seek Time = "+cylinders+" cylinders");
    }
}
