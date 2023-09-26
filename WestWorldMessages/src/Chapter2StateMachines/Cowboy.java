package Chapter2StateMachines;

import common.Messaging.Telegram;
import Chapter2StateMachines.CowboyOwnedStates.CowboyGlobalState;
import Chapter2StateMachines.CowboyOwnedStates.DoCowboyWork;
import Chapter2StateMachines.CowboyOwnedStates.DoEatStew;
import static Chapter2StateMachines.MessageDispatcher.SEND_MSG_IMMEDIATELY;


import static common.windows.*;

public class Cowboy extends BaseGameEntity {
    private StateMachine<Cowboy> m_pStateMachine;
    private location_type m_Location;
    private static final int MaxHunger = 5; // Maximum hunger level
    private int m_iHunger; // Current hunger level
    private MessageDispatcher m_dispatcher; // Reference to the MessageDispatcher

    public Cowboy(EntityNames id) {
        super(id);
        m_Location = location_type.shack;
        m_pStateMachine = new StateMachine<Cowboy>(this);
        m_pStateMachine.SetCurrentState(DoCowboyWork.Instance());
        m_pStateMachine.SetGlobalState(CowboyGlobalState.Instance());
        m_iHunger = 0; // Initialize hunger level to zero

        // Get the singleton instance of the MessageDispatcher
        m_dispatcher = MessageDispatcher.Instance();
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        m_pStateMachine = null;
    }

    
    // Method to send a message to Cowboy when the wife is preparing stew and hungry
    private void SendStewReadyMessageToCowboy() {
        if (m_pStateMachine.isInState(DoCowboyWork.Instance()) && m_iHunger >= MaxHunger) {
            // Send the message to Cowboy using the MessageDispatcher reference
            m_dispatcher.DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), EntityNames.ent_Cowboy.id, MessageTypes.Msg_StewReady, null);
        }
    }

    @Override
    public void Update() {
        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        SendStewReadyMessageToCowboy();
        m_pStateMachine.Update();

        // Handle messages and print any relevant information
        while (!m_pStateMachine.GetMessageQueue().isEmpty()) {
            Telegram msg = m_pStateMachine.GetMessageQueue().poll();
            // Handle the message here or print any relevant information
            // For example, you can print the message content like this:
            System.out.println("Cowboy received message: " + msg.Msg);
        }

    }

    private void SetTextColor(int i) {
    }

    @Override
    public boolean HandleMessage(Telegram msg) {
        return m_pStateMachine.HandleMessage(msg);
    }

    public StateMachine<Cowboy> GetFSM() {
        return m_pStateMachine;
    }

    public location_type GetLocation() {
        return m_Location;
    }

    public void SetLocation(location_type location) {
        m_Location = location;
    }


    // Method to update the cowboy's hunger level
    public void UpdateHunger(int amount) {
        m_iHunger += amount;
        m_iHunger = Math.max(0, m_iHunger); // Ensure hunger level is non-negative
    }
}