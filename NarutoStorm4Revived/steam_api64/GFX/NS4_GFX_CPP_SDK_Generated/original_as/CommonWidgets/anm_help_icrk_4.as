package shop_icrk_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol17")]
   public dynamic class anm_help_icrk_4 extends MovieClip
   {
      
      public var txt_help:smb_font;
      
      public function anm_help_icrk_4()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_help.SetText("アイテム説明テキスト");
         this.txt_help.SetTextSize(29);
         this.txt_help.SetTextColor(0);
         this.txt_help.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_help.SetTextFieldWidth(1400);
         this.txt_help.SetTextWordWrap(true);
      }
   }
}

