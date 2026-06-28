package freebtl_cp_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol65")]
   public dynamic class anm_cap_eff00_27 extends MovieClip
   {
      
      public var mc_eff_light02:MovieClip;
      
      public var mc_eff_light01:MovieClip;
      
      public function anm_cap_eff00_27()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function fl_RotateContinuously_6(param1:Event) : *
      {
         this.mc_eff_light01.rotation += 1;
      }
      
      public function fl_RotateContinuously_7(param1:Event) : *
      {
         this.mc_eff_light02.rotation += 1;
      }
      
      internal function frame1() : *
      {
         this.mc_eff_light01.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_6);
         this.mc_eff_light02.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_7);
      }
   }
}

