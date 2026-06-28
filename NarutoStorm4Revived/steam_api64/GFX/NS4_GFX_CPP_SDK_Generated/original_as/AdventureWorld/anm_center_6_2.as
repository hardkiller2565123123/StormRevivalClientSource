package duel_lock_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol11")]
   public dynamic class anm_center_6 extends MovieClip
   {
      
      public var mc_eff:MovieClip;
      
      public function anm_center_6()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function fl_RotateContinuously(param1:Event) : *
      {
         this.mc_eff.rotation += 4;
      }
      
      internal function frame1() : *
      {
         this.mc_eff.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously);
      }
   }
}

