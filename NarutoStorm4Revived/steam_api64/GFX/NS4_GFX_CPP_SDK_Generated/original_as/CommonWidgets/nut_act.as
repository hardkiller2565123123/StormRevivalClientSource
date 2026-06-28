package script.duel_boss_act
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public class nut_act extends MovieClip
   {
      
      private static const CCD_LOOP_FRAME:uint = 20;
      
      public function nut_act()
      {
         super();
         addFrameScript(19,this.frame20,32,this.frame33,33,this.frame34,45,this.frame46);
         stop();
      }
      
      public function IsOutAnm() : Boolean
      {
         var _loc1_:Boolean = false;
         if(currentFrame > CCD_LOOP_FRAME)
         {
            _loc1_ = true;
         }
         return _loc1_;
      }
      
      public function IsEndOutAnm() : Boolean
      {
         var _loc1_:Boolean = false;
         if(currentLabel == "ng_end" || currentLabel == "ok_end")
         {
            _loc1_ = true;
         }
         return _loc1_;
      }
      
      internal function frame20() : *
      {
         this.stop();
      }
      
      internal function frame33() : *
      {
         this.stop();
      }
      
      internal function frame34() : *
      {
         this.stop();
      }
      
      internal function frame46() : *
      {
         this.stop();
      }
   }
}

