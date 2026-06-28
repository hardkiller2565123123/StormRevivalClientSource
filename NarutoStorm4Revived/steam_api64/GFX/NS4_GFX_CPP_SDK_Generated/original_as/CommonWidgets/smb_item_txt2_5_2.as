package cutin_get_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol13")]
   public dynamic class smb_item_txt2_5 extends MovieClip
   {
      
      public var txt_cond:smb_font;
      
      public var txt_mtr:smb_font;
      
      public function smb_item_txt2_5()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_mtr.SetText("プラチナクナイABCgy_:123");
         this.txt_cond.SetText("プラチナクナイABCgy_:123");
         this.txt_mtr.SetTextSize(28);
         this.txt_mtr.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_mtr.SetTextColor(16766815);
         this.txt_cond.SetTextSize(28);
         this.txt_cond.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_cond.SetTextColor(16766815);
      }
   }
}

