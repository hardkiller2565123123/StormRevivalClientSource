package script.infoData
{
   public class OugiFinInfoDataManager extends InfoDataManagerBase
   {
      
      public function OugiFinInfoDataManager(param1:Array)
      {
         var _loc4_:InfoDataBase = null;
         super();
         var _loc2_:int = int(param1.length);
         m_dataList = new Array(_loc2_);
         var _loc3_:int = 0;
         while(_loc3_ < _loc2_)
         {
            m_dataList[_loc3_] = new OugiFinInfoData(param1[_loc3_]);
            _loc4_ = m_dataList[_loc3_];
            if(_loc4_.m_isNew)
            {
               m_newIconCheckItemKeyList.push(_loc4_.m_saveIdx);
            }
            _loc3_++;
         }
      }
      
      public function GetData(param1:int) : OugiFinInfoData
      {
         var _loc2_:OugiFinInfoData = null;
         if(param1 >= 0 && param1 < m_dataList.length)
         {
            _loc2_ = m_dataList[param1];
         }
         return _loc2_;
      }
   }
}

