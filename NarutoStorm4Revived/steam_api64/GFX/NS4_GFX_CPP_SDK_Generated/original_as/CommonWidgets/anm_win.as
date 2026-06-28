package script.net_set
{
   import flash.display.MovieClip;
   import script.net_cmn.smb_index;
   import script.net_cmn.smb_win;
   import script.xcmn_font.smb_font;
   import script.xct_deco1.nut_deco1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public dynamic class anm_win extends MovieClip
   {
      
      public var txt_head:smb_font;
      
      public var mc_index:smb_index;
      
      public var all_deco1:nut_deco1;
      
      public var mc_win:smb_win;
      
      public function anm_win()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_head.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_head.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_head.SetTextSize(33);
      }
   }
}

