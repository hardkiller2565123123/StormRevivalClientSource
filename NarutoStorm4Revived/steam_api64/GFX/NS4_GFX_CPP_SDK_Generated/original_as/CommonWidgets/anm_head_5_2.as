package shop_icrk_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol18")]
   public dynamic class anm_head_5 extends MovieClip
   {
      
      public var txt_head_name:smb_font;
      
      public function anm_head_5()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_head_name.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_head_name.SetTextColor(16777215);
         this.txt_head_name.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_head_name.SetTextSize(30);
      }
   }
}

