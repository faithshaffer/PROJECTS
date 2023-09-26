package Chapter2StateMachines.CowboyOwnedStates;

import common.Messaging.Telegram;
import Chapter2StateMachines.Cowboy;
import Chapter2StateMachines.State;
import static common.misc.ConsoleUtils.*;
import static Chapter2StateMachines.EntityNames.*;

public class DoGunfight extends State<Cowboy> {

    static final DoGunfight instance = new DoGunfight();

    private DoGunfight() {
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        throw new CloneNotSupportedException("Cloning not allowed");
    }

    public static DoGunfight Instance() {
        return instance;
    }

    @Override
    public void Enter(Cowboy cowboy) {
        cout("\n" + GetNameOfEntity(cowboy.ID()) + ": Get ready for a gunfight!");
    }

    @Override
    public void Execute(Cowboy cowboy) {
        cout("\n" + GetNameOfEntity(cowboy.ID()) + ": Bang bang! Pew pew!");
    }

    @Override
    public void Exit(Cowboy cowboy) {
        cout("\n" + GetNameOfEntity(cowboy.ID()) + ": Exiting gunfight!");
        //cowboy.GetFSM().ChangeState(State.Instance());
    }

    @Override
    public boolean OnMessage(Cowboy cowboy, Telegram msg) {
        return false;
    }
}