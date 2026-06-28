package duel_boss_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol87")]
   public dynamic class anm_stk_s2_27 extends MovieClip
   {
      
      public var mc_sdw:MovieClip;
      
      public function anm_stk_s2_27()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function fl_RotateContinuously_6(param1:Event) : *
      {
         this.mc_sdw.rotation += 45;
      }
      
      internal function frame1() : *
      {
         this.mc_sdw.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_6);
      }
   }
}

