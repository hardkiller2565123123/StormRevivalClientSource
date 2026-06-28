package msg_wins_m_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import script.xcmn_eff2.smb_xef_sun1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol6")]
   public dynamic class anm_eff_sun_6 extends MovieClip
   {
      
      public var mc_xef_sun1:smb_xef_sun1;
      
      public function anm_eff_sun_6()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function fl_RotateContinuously_4(param1:Event) : *
      {
         this.mc_xef_sun1.rotation += 0.3;
      }
      
      internal function frame1() : *
      {
         this.mc_xef_sun1.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_4);
      }
   }
}

