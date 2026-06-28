package net_rank_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol8")]
   public dynamic class smb_head_11 extends MovieClip
   {
      
      public var txt_sort:smb_font;
      
      public function smb_head_11()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_sort.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_sort.SetTextColor(16774492);
         this.txt_sort.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_sort.SetTextSize(smb_font.CCD_FONT_SIZE_LARGE);
      }
   }
}

