package shop_vo_fla
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol6")]
   public dynamic class anm_head_8 extends MovieClip
   {
      
      public var txt_head_cos:smb_font;
      
      public var txt_head_price:smb_font;
      
      public var pos:Point;
      
      public var tmp:Point;
      
      public function anm_head_8()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_head_cos.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_head_cos.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_head_cos.SetTextSize(33);
         this.txt_head_price.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_head_price.SetTextSize(30);
         if(this.txt_head_cos.IsArabic() == true)
         {
            this.pos = new Point();
            this.tmp = new Point();
            this.txt_head_cos.GetTextPos(this.pos);
            this.txt_head_price.GetTextPos(this.tmp);
            this.txt_head_cos.SetTextPos(this.tmp.x,this.pos.y);
            this.txt_head_price.SetTextPos(this.pos.x,this.tmp.y);
            this.txt_head_cos.SetTextPivot(smb_font.CCD_PIVOT_CC);
            this.txt_head_price.SetTextPivot(smb_font.CCD_PIVOT_LC);
            this.txt_head_cos.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.txt_head_price.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
      }
   }
}

