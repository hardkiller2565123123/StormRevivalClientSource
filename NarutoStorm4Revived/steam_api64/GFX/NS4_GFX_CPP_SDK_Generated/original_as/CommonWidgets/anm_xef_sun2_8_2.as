package freebtl_cp_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import script.xcmn_eff2.smb_xef_sun1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol14")]
   public dynamic class anm_xef_sun2_8 extends MovieClip
   {
      
      public var mc_xef_sun2:smb_xef_sun1;
      
      public var mc_xef_sun1:smb_xef_sun1;
      
      public function anm_xef_sun2_8()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function fl_RotateContinuously_5(param1:Event) : *
      {
         this.mc_xef_sun1.rotation += 0.2;
      }
      
      public function fl_RotateContinuously_8(param1:Event) : *
      {
         this.mc_xef_sun2.rotation += 0.3;
      }
      
      internal function frame1() : *
      {
         this.mc_xef_sun1.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_5);
         this.mc_xef_sun2.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_8);
      }
   }
}

