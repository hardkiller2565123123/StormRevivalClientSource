package script.map_sm
{
   import flash.display.MovieClip;
   import script.xcmn_menu.nut_cursol_s;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol40")]
   public class anm_cursor extends MovieClip
   {
      
      private static const CCD_MARGIN:Number = 6;
      
      public var down_cursor:nut_cursol_s;
      
      public var left_cursor:nut_cursol_s;
      
      public var right_cursor:nut_cursol_s;
      
      public var up_cursor:nut_cursol_s;
      
      private var m_leftLimit:Number = 0;
      
      private var m_rightLimit:Number = 0;
      
      private var m_upLimit:Number = 0;
      
      private var m_downLimit:Number = 0;
      
      private var m_leftCursor:MovieClip = null;
      
      private var m_rightCursor:MovieClip = null;
      
      private var m_upCursor:MovieClip = null;
      
      private var m_downCursor:MovieClip = null;
      
      public function anm_cursor()
      {
         super();
         this.m_leftCursor = this["left_cursor"];
         this.m_rightCursor = this["right_cursor"];
         this.m_upCursor = this["up_cursor"];
         this.m_downCursor = this["down_cursor"];
      }
      
      public function SetLimitPos(param1:Number, param2:Number, param3:Number, param4:Number) : *
      {
         this.m_leftLimit = param1 + CCD_MARGIN;
         this.m_rightLimit = param2 - CCD_MARGIN;
         this.m_upLimit = param3 + CCD_MARGIN;
         this.m_downLimit = param4 - CCD_MARGIN;
      }
      
      public function Update(param1:Number, param2:Number, param3:Number) : *
      {
         this.m_leftCursor.alpha = 1;
         this.m_rightCursor.alpha = 1;
         this.m_upCursor.alpha = 1;
         this.m_downCursor.alpha = 1;
         if(param1 - param3 <= this.m_leftLimit)
         {
            this.m_leftCursor.alpha = 0;
         }
         else if(param1 + param3 >= this.m_rightLimit)
         {
            this.m_rightCursor.alpha = 0;
         }
         if(param2 - param3 <= this.m_upLimit)
         {
            this.m_upCursor.alpha = 0;
         }
         else if(param2 + param3 >= this.m_downLimit)
         {
            this.m_downCursor.alpha = 0;
         }
      }
   }
}

