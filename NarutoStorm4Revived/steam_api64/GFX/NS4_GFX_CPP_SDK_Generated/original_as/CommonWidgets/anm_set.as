package script.collect_vo
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base4;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public class anm_set extends MovieClip
   {
      
      internal static const CCD_MARGIN:Number = 50;
      
      public var mc_set_base:nut_base4;
      
      public var txt_set:smb_font;
      
      public var txt_set_num:smb_font;
      
      private var m_txtSet:smb_font = null;
      
      private var m_txtSetNum:smb_font = null;
      
      private var m_base:MovieClip = null;
      
      private var m_isChangeLayout:Boolean = false;
      
      public function anm_set()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_txtSet = this["txt_set"];
         this.m_txtSetNum = this["txt_set_num"];
         this.m_base = this["mc_set_base"];
      }
      
      public function SetTextMenu(param1:String) : *
      {
         if(this.m_txtSet != null)
         {
            this.m_txtSet.SetText(param1);
            this.CalcTextPos();
         }
      }
      
      public function SetTextNumber(param1:String, param2:Array) : *
      {
         if(this.m_txtSetNum != null)
         {
            this.m_txtSetNum.SetText(param1,param2);
            this.CalcTextPos();
         }
      }
      
      private function CheckArabicLayout() : *
      {
         var _loc1_:Point = null;
         var _loc2_:Point = null;
         if(this.m_txtSet != null && this.m_txtSetNum != null && this.m_txtSet.IsArabic() == true)
         {
            _loc1_ = new Point();
            _loc2_ = new Point();
            this.m_txtSet.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtSet.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_txtSet.GetTextPos(_loc1_);
            this.m_txtSetNum.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtSetNum.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_txtSetNum.GetTextPos(_loc2_);
            this.m_txtSet.SetTextPos(_loc2_.x,_loc2_.y);
            this.m_txtSetNum.SetTextPos(_loc1_.x,_loc1_.y);
            this.m_isChangeLayout = true;
         }
      }
      
      private function CalcTextPos() : *
      {
         var _loc1_:Point = null;
         if(this.m_isChangeLayout == false)
         {
            return;
         }
         if(this.m_txtSet != null && this.m_txtSetNum != null)
         {
            _loc1_ = new Point();
            this.m_txtSet.GetTextPos(_loc1_);
            _loc1_.x -= this.m_txtSet.GetTextFieldWidth() + CCD_MARGIN;
            this.m_txtSetNum.SetTextPos(_loc1_.x,_loc1_.y);
         }
      }
      
      internal function frame1() : *
      {
         this.txt_set.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_set.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_set.SetTextSize(26);
         this.txt_set_num.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_set_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_set_num.SetTextSize(28);
         this.CheckArabicLayout();
      }
   }
}

