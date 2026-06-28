package shop_cmn_fla
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import script.xct_bg_deco.smb_stamp3;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol12")]
   public dynamic class anm_stamp3_11 extends MovieClip
   {
      
      public var mc_deco1:smb_stamp3;
      
      public function anm_stamp3_11()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function fl_RotateContinuously_4(param1:Event) : *
      {
         this.mc_deco1.rotation += 0.1;
      }
      
      internal function frame1() : *
      {
         this.mc_deco1.addEventListener(Event.ENTER_FRAME,this.fl_RotateContinuously_4);
      }
   }
}

