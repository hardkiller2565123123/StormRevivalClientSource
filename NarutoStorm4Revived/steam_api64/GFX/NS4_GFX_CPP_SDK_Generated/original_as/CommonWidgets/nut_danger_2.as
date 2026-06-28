package script.duel_boss_danger
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol10")]
   public class nut_danger extends MovieClip
   {
      
      public var End:Function;
      
      public function nut_danger()
      {
         super();
         addFrameScript(25,this.frame26,32,this.frame33);
         visible = false;
      }
      
      public function Start() : *
      {
         visible = true;
         gotoAndPlay("in");
         addEventListener(Event.ENTER_FRAME,this.OnUpdate);
      }
      
      public function OnUpdate(param1:Event) : *
      {
         if(currentFrame == 33)
         {
            this.End();
            visible = false;
            removeEventListener(Event.ENTER_FRAME,this.OnUpdate);
         }
      }
      
      public function Reset() : *
      {
         this.End();
         visible = false;
         removeEventListener(Event.ENTER_FRAME,this.OnUpdate);
      }
      
      internal function frame26() : *
      {
      }
      
      internal function frame33() : *
      {
         this.stop();
      }
   }
}

