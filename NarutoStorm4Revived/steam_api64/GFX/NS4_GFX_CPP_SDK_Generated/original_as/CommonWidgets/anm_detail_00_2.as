package script.result_main
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base7;
   import script.xcmn_menu.nut_line2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol138")]
   public class anm_detail_00 extends MovieClip
   {
      
      public var mc_detail_base:nut_base7;
      
      public var mc_line:nut_line2;
      
      public var txt_form:smb_font;
      
      public var txt_name:smb_font;
      
      public var txt_total:smb_font;
      
      internal var m_name:smb_font = null;
      
      internal var m_form:smb_font = null;
      
      internal var m_total:smb_font = null;
      
      internal var m_isChangedLayout:Boolean = false;
      
      public function anm_detail_00()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_name = this["txt_name"];
         this.m_form = this["txt_form"];
         this.m_total = this["txt_total"];
      }
      
      public function SetTextDetail(param1:String, param2:String, param3:String) : *
      {
         var _loc4_:Point = null;
         if(this.m_name != null && this.m_form != null && this.m_total != null)
         {
            this.m_name.SetText(param1);
            this.m_form.SetText(param2);
            this.m_total.SetText(param3);
            if(this.m_isChangedLayout == true)
            {
               _loc4_ = new Point();
               this.m_form.GetTextPos(_loc4_);
               _loc4_.x += this.m_form.GetTextFieldWidth();
               this.m_total.SetTextPos(_loc4_.x,_loc4_.y);
            }
         }
      }
      
      private function CheckArabicLayout() : *
      {
         var _loc1_:Point = null;
         var _loc2_:Point = null;
         if(this.m_isChangedLayout == true)
         {
            return;
         }
         if(this.m_name != null && this.m_form != null && this.m_total != null && this.m_name.IsArabic() == true)
         {
            _loc1_ = new Point();
            this.m_name.GetTextPos(_loc1_);
            this.m_name.SetTextPos(-_loc1_.x,_loc1_.y);
            this.m_name.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_name.SetTextPivot(smb_font.CCD_PIVOT_RC);
            _loc2_ = new Point();
            this.m_form.GetTextPos(_loc2_);
            this.m_total.GetTextPos(_loc1_);
            this.m_form.SetTextPos(-_loc1_.x,_loc1_.y);
            this.m_total.SetTextPos(-_loc2_.x,_loc2_.y);
            this.m_form.SetTextPivot(smb_font.CCD_PIVOT_LC);
            this.m_form.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_total.SetTextPivot(smb_font.CCD_PIVOT_LC);
            this.m_total.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_isChangedLayout = true;
         }
      }
      
      internal function frame1() : *
      {
         this.txt_name.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_name.SetTextSize(30);
         this.txt_name.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_name.SetTextRubyEnable(false);
         this.txt_form.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_form.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_form.SetTextSize(33);
         this.txt_form.SetTextRubyEnable(false);
         this.txt_total.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_total.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_total.SetTextSize(33);
         this.txt_total.SetTextRubyEnable(false);
         this.CheckArabicLayout();
      }
   }
}

