package hist_cmn_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol38")]
   public dynamic class anm_road_60 extends MovieClip
   {
      
      public var txt_road:smb_font;
      
      public function anm_road_60()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_road.SetTextSize(28);
         this.txt_road.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_road.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

