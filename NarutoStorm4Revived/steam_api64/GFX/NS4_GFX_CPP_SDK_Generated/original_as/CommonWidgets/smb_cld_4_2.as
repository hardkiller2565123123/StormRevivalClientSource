package map_sm_brt_fla
{
   import flash.display.MovieClip;
   import script.xcmn_btn_plat.all_btn_plat;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol68")]
   public dynamic class smb_cld_4 extends MovieClip
   {
      
      public var all_icon2:all_btn_plat;
      
      public function smb_cld_4()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.all_icon2.gotoAndStop("btn_4");
      }
   }
}

