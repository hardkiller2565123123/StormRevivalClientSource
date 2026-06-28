package cutin_msion_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import script.xcmn_eff2.smb_xef_dus3;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol13")]
   public dynamic class anm_c_eff_10 extends MovieClip
   {
      
      public var mc_c_eff01:smb_xef_dus3;
      
      public var mc_c_eff02:smb_xef_dus3;
      
      public function anm_c_eff_10()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function fl_RotateContinuously_5(param1:Event) : *
      {
         this.mc_c_eff01.rotation += 0.5;
      }
      
      public function fl_RotateContinuously_6(param1:Event) : *
      {
         this.mc_c_eff02.rotation += 0.3;
      }
      
      internal function frame1() : *
      {
         this.mc_c_eff01.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_5);
         this.mc_c_eff02.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_6);
      }
   }
}

