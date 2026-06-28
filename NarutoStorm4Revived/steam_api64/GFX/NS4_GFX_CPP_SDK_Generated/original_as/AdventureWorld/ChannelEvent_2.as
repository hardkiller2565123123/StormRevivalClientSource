package script.gametitle_lu.events
{
   import flash.events.Event;
   
   public class ChannelEvent extends Event
   {
      
      public static const CHANGE:String = "channelChange";
      
      public var value:int;
      
      public function ChannelEvent(value:int)
      {
         super(CHANGE,true,false);
         this.value = value;
      }
      
      override public function clone() : Event
      {
         return new ChannelEvent(value);
      }
   }
}

